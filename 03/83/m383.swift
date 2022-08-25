// Solved:
// (E) Ransom Note
// https://leetcode.com/problems/ransom-note/

class Solution {
	func canConstruct(_ ransomNote: String, _ magazine: String) -> Bool {
		var charFreq = Array<Int>(repeating: 0, count: 26)
		for ch in magazine {
			// Counting all chars
			if let ch = ch.asciiValue {
				charFreq[Int(ch) - 97] += 1 // 97 = 'a'
			}
		}
		for ch in ransomNote {
			if let ch = ch.asciiValue {
				let x = Int(ch) - 97  // 97 = 'a'
				if charFreq[x] > 0 { charFreq[x] -= 1 }
				else { return false }
			}
		}
		return true
	}
}
