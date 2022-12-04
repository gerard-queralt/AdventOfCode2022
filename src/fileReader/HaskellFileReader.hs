module HaskellFileReader where
  readInputOfDay :: Int -> IO String
  readInputOfDay day = do
    let dayInputPath = "..\\day" ++ (show day) ++ "\\input.txt"
    inputFile <- readFile dayInputPath
    return inputFile

  splitStringAt :: String -> Char -> [String]
  splitStringAt s splitAt =
    case break (==splitAt) s of
      (s1, splitAt:s2) -> s1 : splitStringAt s2 splitAt
      (s1, "") -> [s1]