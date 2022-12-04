import HaskellFileReader

isOnePairContained :: [String] -> Bool
isOnePairContained [range1, range2] = isContained
  where
    [start1, end1] = map (\val -> read val :: Int) $ splitStringAt range1 '-'
    [start2, end2] = map (\val -> read val :: Int) $ splitStringAt range2 '-'
    range1ContainedInRange2 = (start2 <= start1) && (end1 <= end2)
    range2ContainedInRange1 = (start1 <= start2) && (end2 <= end1)
    isContained = range1ContainedInRange2 || range2ContainedInRange1

containedRangesInPairs :: [String] -> Int
containedRangesInPairs listOfPairs = containedRanges
  where
    separatedPairs = map (\pairLine -> splitStringAt pairLine ',') listOfPairs
    containedRanges = length $ filter id $ map isOnePairContained separatedPairs

arePairsOverlapped :: [String] -> Bool
arePairsOverlapped [range1, range2] = overlapped
  where
    [start1, end1] = map (\val -> read val :: Int) $ splitStringAt range1 '-'
    [start2, end2] = map (\val -> read val :: Int) $ splitStringAt range2 '-'
    overlapped = (start1 <= end2) && (start2 <= end1)

overlappedPairs :: [String] -> Int
overlappedPairs listOfPairs = overlappedRanges
  where
    separatedPairs = map (\pairLine -> splitStringAt pairLine ',') listOfPairs
    overlappedRanges = length $ filter id $ map arePairsOverlapped separatedPairs

main :: IO ()
main = do
  input <- readInputOfDay 4
  print $ "Part 1: " ++ (show $ containedRangesInPairs $ lines input)
  print $ "Part 2: " ++ (show $ overlappedPairs $ lines input)