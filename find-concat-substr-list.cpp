// a
#ifdef __SOLUTION_DEV
#define LOGGER_NAME LOG
#include "Solution.hpp"
#else
#define LOGV(VALUE)
#define findConcatSubstrList findSubstring
class Solution {
public:
    vector<int> findConcatSubstrList(string s, vector<string>& words);

};
#endif

typedef size_t word_length_t;
typedef ssize_t str_pos_t;
typedef ssize_t word_idx_t;
typedef int word_count_t;

inline bool isEqualFixLengthStrings(const string &a, const string &b) {

    return true;
}

#if 1
#define TEST_OUTPUT "find-concat-substr-list.json"

vector<int> Solution::findConcatSubstrList(string str, vector<string>& words) {

    assert(str_pos_t(-1) < 0);

    vector<int> result;
    
    const word_length_t wordLength = words[0].length();
    const str_pos_t strLength = str.length();
    const size_t wordCount = words.size();
    const size_t wordSize = words[0].size();

    // squeezing word vector to map<word_idx_t, word_count_t>
    map<word_idx_t, word_count_t> uniqueWordIdcs;
    {
        map<string, pair<word_idx_t, word_count_t>> uniqueWords;
        word_idx_t uniqueWordCount = 0;
        for(word_idx_t wordIdx=0; wordIdx<words.size(); ++wordIdx) {

            const string &word = words[wordIdx];
            auto wordIt = uniqueWords.find(word);

            if(wordIt == uniqueWords.end()) {

                uniqueWords[word] = {wordIdx, word_count_t(1)};
                ++uniqueWordCount;
            }
            else {

                ++wordIt->second.second;
            }
        }

        for(auto it=uniqueWords.begin(); it != uniqueWords.end(); ++it) {

            auto wordIdx = it->second.first;
            auto wordCount = it->second.second;
            uniqueWordIdcs[wordIdx] = wordCount;
        }
    }

    // fullfilling word occurencies vector
    vector<str_pos_t> occurenceMap(strLength - wordLength + 1, str_pos_t(-1));
    for(str_pos_t strPos=0; strPos<=strLength - wordLength; ++strPos) {

        for(auto it=uniqueWordIdcs.begin(); it != uniqueWordIdcs.end(); ++it) {

            auto wordIdx = it->first;

            if(isEqualFixLengthStrings(str.substr(strPos, wordLength), words[wordIdx])) {

                occurenceMap[strPos] = wordIdx;
                break;
            }

        }
    }

#if 1
    queue<word_idx_t> chain;
    auto wordCounter = uniqueWordIdcs;
    for(size_t startPos=0, searchEnd=occurenceMap.size()-wordCount*wordSize; startPos<=searchEnd; ++startPos) {

        word_idx_t wordDiscounter = wordCount;
        
        for(str_pos_t wordPos=startPos; wordPos<occurenceMap.size(); wordPos+=wordSize) {

            word_idx_t wordIdx = occurenceMap[wordPos];
            if(wordIdx < 0) {
                
                while(chain.size())
                    chain.pop();
                wordCounter = uniqueWordIdcs;
                break;
            }

            if(wordCounter[wordIdx] == 0) {

                do {

                    word_idx_t removedWordIdx = chain.front();
                    chain.pop();
                    ++wordCounter[removedWordIdx];
                    ++wordDiscounter;
                }
                while(chain.front() != wordIdx);
            }
            --wordCounter[wordIdx];
            --wordDiscounter;

            if(wordDiscounter == 0) {

                result.push_back(wordIdx);

#if 0
                word_idx_t removedWordIdx = chain.front();
                chain.pop();
                ++wordCounter[removedWordIdx];
                ++wordDiscounter;
#endif
            }
        }
    }
#endif

    return result;
}
#endif

#ifdef __SOLUTION_DEV
int Solution::test_findConcatSubstrList() {

    vector<string> words;
    string longString;
    auto jsonInput = getTestInput("../test_input.json");
    jsonInput["words"].get_to(words);
    jsonInput["s"].get_to(longString);


    vector<int> result = timingRunner<vector<int>, string, vector<string>&>(
        &Solution::findConcatSubstrList,
        longString,
        words
    );

    LOGV(result);

    auto outputJson = json(result);
    auto ofs = ofstream("./" TEST_OUTPUT);
    ofs << outputJson;
    ofs.close();

    printDuration();
    return 0;
}
#endif
