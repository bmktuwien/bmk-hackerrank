{-# LANGUAGE FlexibleInstances, UndecidableInstances, DuplicateRecordFields #-}

module Main where

import           Control.Monad
import qualified Data.ByteString.Char8 as C
import           Data.Bits
import           Data.List
import qualified Data.Map.Strict       as Map
import qualified Data.IntMap.Strict    as IntMap
import           Debug.Trace

-- precompute factorials
compFactorials :: Int -> Int -> IntMap.IntMap Int
compFactorials n m = go 0 1 IntMap.empty
  where
    go a acc map
      | a < 0     = map
      | a < n     = go a' acc' map'
      | otherwise = map'
      where
        map' = IntMap.insert a acc map
        a'   = a + 1
        acc' = (acc * a') `mod` m

-- precompute invs
compInvs :: Int -> Int -> IntMap.IntMap Int -> IntMap.IntMap Int
compInvs n m facts = go 0 IntMap.empty
  where
    go a map
      | a < 0     = map
      | a < n     = go a' map'
      | otherwise = map'
      where
        map' = IntMap.insert a v map
        a' = a + 1
        v = (modExp b (m-2) m) `mod` m
        b = (IntMap.!) facts a


modExp :: Int -> Int -> Int -> Int
modExp b e m = go b e 1
  where
    go b e r
      | (.&.) e 1 == 1 = go b' e' r'
      | e > 0 = go b' e' r
      | otherwise = r
        where
          r' = (r * b) `mod` m
          b' = (b * b) `mod` m
          e' = shift e (-1)

-- precompute frequency table
initFreqMap :: C.ByteString -> Map.Map Char (IntMap.IntMap Int)
initFreqMap inp = go 1 map1 map2 inp
  where
    map1 = Map.fromList $ zip ['a'..'z'] $ repeat 0
    map2 = Map.fromList $ zip ['a'..'z'] $ repeat IntMap.empty

    go idx m1 m2 inp
      | C.null inp = m2
      | otherwise  = go (idx+1) m1' m2' $ C.tail inp
      where
        m1' = Map.update (\v -> Just $ v+1) (C.head inp) m1
        m2' = foldl' (\m w -> Map.update (\v -> liftM (\c -> IntMap.insert idx c v) $
              Map.lookup w m1') w m) m2 ['a'..'z']


query :: Int -> Int -> Int -> Map.Map Char (IntMap.IntMap Int)
         -> IntMap.IntMap Int -> IntMap.IntMap Int -> Int
query l r m freqMap facts invs
  | x > 1     = (x * y) `mod` m
  | otherwise = y
  where
    calcCnt cs = cr - cl
      where
         cl = IntMap.findWithDefault 0 (l-1) cs
         cr = IntMap.findWithDefault 0 r cs

    f1 acc cs
      | even cnt = acc
      | otherwise = acc + 1
      where
        cnt = calcCnt cs

    f2 (acc1,acc2) cs
      | cnt < 2   = (acc1 ,acc2)
      | otherwise = (acc1',acc2')
      where
        cnt = calcCnt cs

        n = cnt `div` 2

        acc1' = acc1 + n
        r = choose acc1' n
        acc2' = (acc2 * r) `mod` m


    -- calc binomial coefficient using Fermat's little theorem
    choose n k
      | n < k = 0
      | otherwise = (f1 * t) `mod` m
      where
        f1 = (IntMap.!) facts n
        i1 = (IntMap.!) invs k
        i2 = (IntMap.!) invs (n-k)

        t = (i1 * i2) `mod` m


    x = Map.foldl' f1 0 freqMap
    y = snd $ Map.foldl' f2 (0,1) freqMap


main :: IO()
main = do
    inp <- C.getLine
    q   <- readLn :: IO Int

    let modulo  = 1000000007
    let facts   = compFactorials (C.length inp) modulo
    let invs    = compInvs (C.length inp) modulo facts
    let freqMap = initFreqMap inp

    forM_ [1..q] $ \_ -> do

      line <- getLine

      let [s1, s2] = words line
      let l = (read s1) :: Int
      let r = (read s2) :: Int

      let result = query l r modulo freqMap facts invs

      putStrLn $ show result
