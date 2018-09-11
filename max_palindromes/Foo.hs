module Main where

import           Control.Monad
import           Data.Array (Array)
import qualified Data.Array as A
import           Data.Map.Strict (Map)
import qualified Data.Map.Strict as M
import           Data.Monoid

newtype Mod1000000007 = Mod Int deriving (Eq, Ord)

instance Num Mod1000000007 where
    fromInteger = Mod . (`mod` 1000000007) . fromInteger
    Mod l + Mod r = Mod ((l+r) `rem` 1000000007)
    Mod l * Mod r = Mod ((l*r) `rem` 1000000007)
    negate (Mod v) = Mod ((1000000007 - v) `rem` 1000000007)
    abs = id
    signum = id

instance Integral Mod1000000007 where
    toInteger (Mod n) = toInteger n
    quotRem a b = (a * b^1000000005, 0)

instance Show Mod1000000007 where show (Mod n) = show n
instance Real Mod1000000007 where toRational (Mod n) = toRational n
instance Enum Mod1000000007 where
    toEnum = Mod . (`mod` 1000000007)
    fromEnum (Mod n) = n

type FactMap = Array Int Mod1000000007

factMap :: Int -> FactMap
factMap n = A.listArray (0,n) (scanl (*) 1 [1..])


type FreqMap = Map Char Int

freqMaps :: String -> Array Int FreqMap
freqMaps s = go where
    go = A.listArray (0, length s)
        (M.empty : [M.insertWith (+) c 1 (go A.! i) | (i, c) <- zip [0..] s])

substringFreqMap :: Array Int FreqMap -> Int -> Int -> FreqMap
substringFreqMap maps l r = M.unionWith (-) (maps A.! r) (maps A.! (l-1))

palindromeCount :: FactMap -> FreqMap -> Mod1000000007
palindromeCount facts freqs
    =     toEnum (max 1 mod2Freqs)
    *     (facts A.! sum div2Freqs)
    `div` product (map (facts A.!) div2Freqs)
    where
    (div2Freqs, Sum mod2Freqs) = foldMap (\n -> ([n `quot` 2], Sum (n `rem` 2))) freqs

main :: IO ()
main = do
    inp <- getLine
    q   <- readLn

    let freqs = freqMaps inp
        facts = factMap (length inp)

    replicateM_ q $ do
        [l,r] <- map read . words <$> getLine
        print . palindromeCount facts $ substringFreqMap freqs l r

