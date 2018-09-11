{-# LANGUAGE FlexibleInstances, UndecidableInstances, DuplicateRecordFields #-}

module Main where

import           Control.Monad
import           Data.Array            (Array)
import qualified Data.Array            as A
import qualified Data.ByteString.Char8 as C
import           Data.Bits
import           Data.List
import qualified Data.Map.Strict       as Map
import qualified Data.IntMap.Strict    as IntMap
import           Debug.Trace


-- precompute factorials
compFactorials :: Int -> Int -> Array Int Int
compFactorials n m = A.listArray (0,n) $ scanl' f 1 [1..n]
  where
    f acc a = (acc * a) `mod` m

-- precompute invs
compInvs :: Int -> Int -> Array Int Int -> Array Int Int
compInvs n m facts = A.listArray (0,n) $ map f [0..n]
  where
    f a = (modExp ((A.!) facts a) (m-2) m) `mod` m

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
initFreqMap :: C.ByteString -> Map.Map Char (Array Int Int)
initFreqMap inp = Map.fromList $ map f ['a'..'z']
  where
    n = C.length inp
    f c = (c, A.listArray (0,n) $ scanl' g 0 [0..n-1])
      where
        g x j
          | C.index inp j == c = x+1
          | otherwise = x

query :: Int -> Int -> Int -> Map.Map Char (Array Int Int)
         -> Array Int Int -> Array Int Int -> Int
query l r m freqMap facts invs
  | x > 1     = (x * y) `mod` m
  | otherwise = y
  where
    calcCnt freqMap = cr - cl
      where
         cl = (A.!) freqMap (l-1)
         cr = (A.!) freqMap r

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
        f1 = (A.!) facts n
        i1 = (A.!) invs k
        i2 = (A.!) invs (n-k)

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

    replicateM_ q $ do

      line <- getLine

      let [s1, s2] = words line
      let l = (read s1) :: Int
      let r = (read s2) :: Int

      let result = query l r modulo freqMap facts invs

      putStrLn $ show result
