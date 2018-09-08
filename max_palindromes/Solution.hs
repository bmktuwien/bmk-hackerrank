{-# LANGUAGE FlexibleInstances, UndecidableInstances, DuplicateRecordFields #-}

module Main where

import Control.Monad
import Data.Array
import Data.Bits
import Data.List
import Data.Set
import Debug.Trace
import System.Environment
import System.IO
import System.IO.Unsafe

query :: Int -> Int -> String
query l r = undefined

main :: IO()
main = do
    s <- getLine
    q <- readLn :: IO Int

    forM_ [1..q] $ \_ -> do
        line <- getLine
        let [s1, s2] = words line
        let l = (read s1) :: Int
        let r = (read s2) :: Int

        let result = query l r

        putStrLn $ show result
