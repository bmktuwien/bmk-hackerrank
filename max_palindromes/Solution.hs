{-# LANGUAGE FlexibleInstances, UndecidableInstances, DuplicateRecordFields #-}

module Main where

import           Control.Monad
import qualified Data.ByteString.Char8 as C
import           Data.Bits
import qualified Data.Map.Strict       as Map


factorials :: Int -> Int -> [Int]
factorials 0 m = [1]
factorials n m = (n * (head s) `mod` m) : s
  where
    s = factorials (n-1) m

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

initFreqMap :: C.ByteString -> Map.Map Char [Int]
initFreqMap inp = go map1 map2 inp
  where
    map1 = Map.fromList $ zip ['a'..'z'] [0..]
    map2 = Map.fromList $ zip ['a'..'z'] $ repeat []

    go m1 m2 inp'
      | C.null inp' = m2
      | otherwise    = go m1' m2' $ C.tail inp'
      where
        w   = C.head inp
        m1' = Map.update (\v -> Just (v+1)) w m1
        m2' = Map.update (\v -> liftM (:v) $ Map.lookup w m1') w m2

query :: Int -> Int -> Int -> Map.Map Char [Int] -> [Int] -> Int
query l r m freqMap facts = undefined
  where
    f1 acc cs
      | even cnt  = 0
      | otherwise = acc + 1
      where
        cl | l > 1     = cs !! (l-2)
           | otherwise = 0

        cr = cs !! (r-2)

        cnt = cr - cl

    --f2 acc 0 = acc
    --f2 acc 1 = acc
    --f2 (acc1,acc2) v = (acc1+v',acc2)
    --  where
    --    v' = v `div` 2

    choose n k = (f1 * t) `mod` m
      where
        f1 = facts !! n
        f2 = facts !! (n-k)

        i1 = (modExp f1 (m-2) m) `mod` m
        i2 = (modExp f2 (m-2) m) `mod` m

        t = (i1 * i2) `mod` m


    x = Map.foldl' f1 0 freqMap
    --(_, y) = Map.foldl' f2 (0,1) freqMap


main :: IO()
main = do
    inp <- C.getLine
    q   <- readLn :: IO Int

    let modulo  = 1000000007
    let facts   = factorials (C.length inp) modulo
    let freqMap = initFreqMap inp

    forM_ [1..q] $ \_ -> do

      line <- getLine

      let [s1, s2] = words line
      let l = (read s1) :: Int
      let r = (read s2) :: Int

      let result = query l r modulo freqMap facts

      putStrLn $ show result
