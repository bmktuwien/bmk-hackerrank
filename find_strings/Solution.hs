{-# LANGUAGE RankNTypes #-}
{-# LANGUAGE FlexibleContexts #-}
{-# LANGUAGE ScopedTypeVariables #-}
{-# LANGUAGE CPP #-}

import           Control.Monad (forM_, replicateM_, replicateM, when)
import           Control.Monad.ST (ST)
import qualified Data.Array.IArray as A
import           Data.Array.IArray (Array, (!))
import           Data.Array.MArray ( newListArray, newArray_
                                   , readArray, writeArray)
import           Data.Array.ST (STUArray, runSTUArray)
import           Data.Array.Unboxed (UArray)
import           Data.Array.Unsafe (unsafeFreeze)
import           Data.List (sortBy)
import           Data.Ord (comparing)
import           Data.STRef ( newSTRef, readSTRef, writeSTRef
                            , modifySTRef')

import           Data.List (group, sort, sortBy, null)
import           Data.Ord (comparing)

import Debug.Trace

data Alpha a = Sentinal Int -- ^ Used to mark the end of a string.
                            -- The `Int` parameter is used to encode
                            -- which string this is the end of, in cases
                            -- where there are multiple.
             | Alpha a -- ^ An actual character in the string.
    deriving (Eq, Ord, Show)

data SuffixArray a = SuffixArray
                       { toSuffixes :: UArray Int Int
                         -- ^ The actual array of suffixes in lexicographic
                         -- order.
                       , toAlphas :: Array Int (Alpha a)
                         -- ^ The original string(s) with `Sentinal` values
                         -- included after each string.
                       , toLcp :: UArray Int Int
                         -- ^ Longest Common Prefix of each suffix with the
                         -- previous one in lexicographic order
                       }
  deriving (Eq, Ord, Show)

type Arr s = STUArray s Int Int

prepare :: [[a]] -> [Alpha a]
prepare = concat . zipWith (\a b -> b ++ [a]) sentinals . map (map Alpha)

rank :: Ord a => [a] -> [Int]
rank = concat . zipWith (map . const) [0 ..] . group

sentinals :: [Alpha a]
sentinals = map Sentinal [0..]

suffixArray :: Ord a => [[a]] -> SuffixArray a
suffixArray xs = SuffixArray ss as lcp
  where
    n = snd $ A.bounds as
    as = let ps = prepare xs
             n' = length ps - 1
          in A.listArray (0, n') ps

    orderedByHead = sortBy (comparing snd) . zip [0 ..] $ A.elems as
    ranked = let (is, js) = unzip orderedByHead
              in zip is (rank js)
    ss :: UArray Int Int
    ss = runSTUArray $ do
      s <- newListArray (0, n) (map fst ranked) -- the suffixes
      r <- newArray_ (0, n) -- the rank of each suffix
      forM_ ranked $ uncurry (writeArray r)
      t <- newArray_ (0, n) -- scratch array
      c <- newArray_ (0, n) -- counts array
      go 1 s r t c

-- After each iteration of `go`, the suffixes are sorted by their
    -- k*2 first characters. k doubles each time, and in each iteration
    -- we do O(n) work and are then ready for the next iteration.
    go :: forall s. Int -> Arr s -> Arr s -> Arr s -> Arr s -> ST s (Arr s)
    go k s r t c
      | k > n = return s
      | otherwise = do
      let getR 0 x = readArray r x
          getR i x = let ix = i + x
                      in if ix > n then return 0
                                   else readArray r ix

          csort i src dest = do
            forM_ [0 .. n] $ flip (writeArray c) 0 -- zero out the counts
            let f = getR i
            -- count how many of each rank there are
            writeArray c 0 i -- takes care of all that would be automatically 0
            forM_ [i .. n] $ \x -> do -- count the appropriate values in r
              x' <- readArray r x
              v <- readArray c x'
              writeArray c x' (v+1)
            -- replace each element in c with the starting index of
            -- elements with that value
            soFar <- newSTRef 0
            forM_ [0 .. n] $ \x -> do
              v <- readArray c x
              readSTRef soFar >>= writeArray c x
              modifySTRef' soFar (+v)
            elemsS <- (A.elems :: UArray Int Int -> [Int]) <$> unsafeFreeze src
            forM_ elemsS $ \x -> do
              r' <- f x -- rank of it
              idx <- readArray c r' -- where it goes, based on its rank
              writeArray c r' (idx + 1) -- next suffix with this rank goes
                                        -- one later
              writeArray dest idx x
      csort k s t -- these two counting sorts comprise a radix sort of the
      csort 0 t s -- suffixes by their rank pairs
      -- now re-rank the suffixes in order
      fstSuffix <- readArray s 0
      prevVal <- ((,) <$> getR 0 fstSuffix <*> getR k fstSuffix) >>= newSTRef
      nextRank <- newSTRef 0
      elemsS <- (A.elems :: UArray Int Int -> [Int]) <$> unsafeFreeze s
      forM_ elemsS $ \x -> do
        val <- (,) <$> getR 0 x <*> getR k x
        val' <- readSTRef prevVal
        -- if its old rank pair is the same as of the previous suffix
        -- (in partially sorted order), it gets the same rank, otherwise
        -- we increase by one
        when (val /= val') $ modifySTRef' nextRank succ
        readSTRef nextRank >>= writeArray t x
        writeSTRef prevVal val
      maxRank <- readSTRef nextRank
      if maxRank < n
        then go (k*2) s t r c -- double the size of the prefix we're sorting by
        else return s -- ranks are already unique for all, stop early
    -- LCP array in the same order as the suffix array
    lcp = A.ixmap (0, n) (ss !) plcp

    plcp = runSTUArray plcp'
    plcp' :: forall s. ST s (Arr s)
    plcp' = do
      -- keep track of what suffix is before each one, in lexicographic
      -- order (the `first` one has none before it, so we treat it special)
      let first = ss ! 0
      (prev :: Arr s) <- newArray_ (0, n)
      forM_ [1 .. n] $ \i -> writeArray prev (ss ! i) (ss ! (i-1))
      len <- newSTRef 0
      res <- newArray_ (0, n)
      forM_ [0 .. n] $ \i ->
        if i == first -- no previous prefix
          then writeSTRef len 0 >> writeArray res i 0
          else do
            len' <- readSTRef len
            prev' <- readArray prev i
            let suffixOff x = map (as !) [x ..]
                newMatching = length . takeWhile id
                            $ zipWith (==) (suffixOff (i + len'))
                                           (suffixOff (prev' + len'))
            writeArray res i (len' + newMatching)
            writeSTRef len $ max 0 (len' + newMatching - 1)
      return res

calcLengthArray :: SuffixArray a -> UArray Int Int
calcLengthArray sa = A.listArray (0,length l - 1) l
  where
    l = init $ scanr f 0 [0..length alphas-1]
    f i c | (Sentinal _) <- (alphas ! i) = 0
          | otherwise = c+1

    alphas = toAlphas sa


query :: SuffixArray a -> Int -> [a]
query sa k = map f $ go 0 $ A.assocs suffixes
  where
    f (Sentinal _) = error "impossible happened"
    f (Alpha a) = a

    go _ [] = []
    go cnt ((j,i):rs)
      | cnt+p >= k = A.elems $ A.ixmap (i,i+x-1) id alphas
      | otherwise = go (cnt+p) rs
        where
          x = (lcps!j)+k-cnt
          p = (ls!i) - (lcps!j)

    ls = calcLengthArray sa

    lcps = toLcp sa
    suffixes = toSuffixes sa
    alphas = toAlphas sa


main :: IO ()
main = do
  n  <- readLn :: IO Int
  ss <- replicateM n getLine

  let sa  = suffixArray ss

  q <- readLn :: IO Int

  replicateM_ q $ do
    k <- readLn :: IO Int

    let res = query sa k

    if null res
      then putStrLn "INVALID"
      else putStrLn res
