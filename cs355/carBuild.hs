{-# LANGUAGE BlockArguments #-}

import System.IO
import Text.Read (readMaybe)

-- Define the frame options
frameOptions :: [String]
frameOptions = ["Coupe", "Sedan", "SUV", "Truck"]

-- Define a function to filter package options based on the frame choice
filterPackageOptions :: String -> [String]
filterPackageOptions frame
  | frame == "SUV" || frame == "Truck" = ["Sport", "Towing", "Luxury", "Custom"]
  | otherwise = ["Sport", "Luxury", "Custom"]

-- Define a function to get a valid user selection from a list of options
getUserSelection :: String -> [String] -> IO String
getUserSelection category options = do
    putStrLn $ "\nSelect a " ++ category ++ ":"
    mapM_ putStrLn $ zipWith (\i option -> show i ++ ". " ++ option) [1..] options
    input <- getLine
    return $ options !! (read input - 1)

-- Function for engine choice
filterEngineOptions :: String -> [String]
filterEngineOptions package
  | package == "Sport" = ["V6", "V6 Turbo", "V8"]
  | package == "Towing" = ["V6", "V8", "Electric"]
  | otherwise = ["4 Cylinder", "V6", "V8", "Electric"]

-- Transmission choices
filterTransmissionOptions :: String -> [String]
filterTransmissionOptions package
  | package == "Sport" = ["3-SA", "4-SA", "CVT", "Dual Gate"]
  | package == "Towing" = ["3-SA", "4-SA", "CVT", "Dual Gate"]
  | otherwise = ["3-SA", "4-SA", "CVT", "Dual Gate"]

-- DriveTrain choices
filterDriveTrain :: String -> [String]
filterDriveTrain package
  | package == "Sport" = ["Front-Wheel", "Rear Wheel", "4/All wheel drive"]
  | package == "Towing" = ["Front-Wheel", "Rear Wheel", "4/All wheel drive"]
  | otherwise = ["Front-Wheel", "Rear Wheel", "4/All wheel drive"]

-- Define a function to display the user's selections
displaySelections :: [String] -> IO ()
displaySelections selections = do
    putStrLn "\n- - - - - -\nYour custom car options:"
    mapM_ putStrLn $ zipWith (\category selection -> category ++ ": " ++ selection) ["Frame", "Package", "Engine", "Transmission", "Drive Train"] selections
    return ()

main :: IO ()
main = do
    hSetBuffering stdout NoBuffering
    putStrLn "Welcome to the Morristown Car Factory! Let's build a car!"

    -- Define the user's selections using IO monadic bind
    frameChoice <- getUserSelection "frame" frameOptions
    let packageOptions = filterPackageOptions frameChoice
    packageChoice <- getUserSelection "package" packageOptions

    let engineOptions = filterEngineOptions packageChoice 
    engineChoice <- getUserSelection "engine" engineOptions

    let transmissionOptions = filterTransmissionOptions packageChoice
    transmissionChoice <- getUserSelection "transmission" transmissionOptions

    let driveTrainOptions = filterDriveTrain packageChoice
    driveTrainChoice <- getUserSelection "Drive Train" driveTrainOptions

    -- Display the user's car build using a dedicated display function
    displaySelections [frameChoice, packageChoice, engineChoice, transmissionChoice, driveTrainChoice]