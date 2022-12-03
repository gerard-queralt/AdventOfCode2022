module HaskellFileReader where
  readInputOfDay :: Int -> IO String
  readInputOfDay day = do
    let dayInputPath = "..\\day" ++ (show day) ++ "\\input.txt"
    inputFile <- readFile dayInputPath
    return inputFile
