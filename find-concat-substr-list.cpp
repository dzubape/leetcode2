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
typedef int16_t str_pos_t;
typedef int16_t word_idx_t;
typedef int16_t word_count_t;

inline bool isEqualFixLengthStrings(const string &a, const string &b) {

    return a == b;
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

    if(wordLength > strLength)
        return result;

    // squeezing word vector to map<word_idx_t, word_count_t>
    map<word_idx_t, word_count_t> wordIdx2wordCountMap;
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
            wordIdx2wordCountMap[wordIdx] = wordCount;
        }
    }

    // fullfilling word occurencies vector
    vector<str_pos_t> wordsEntryMap(strLength - wordLength + 1, str_pos_t(-1));
    for(str_pos_t strPos=0; strPos<=strLength - wordLength; ++strPos) {

        for(auto it=wordIdx2wordCountMap.begin(); it != wordIdx2wordCountMap.end(); ++it) {

            auto wordIdx = it->first;

            if(isEqualFixLengthStrings(str.substr(strPos, wordLength), words[wordIdx])) {

                wordsEntryMap[strPos] = wordIdx;
                break;
            }

        }
    }

#if 1
    queue<word_idx_t> chain;
    for(str_pos_t shift=0; shift<wordSize; ++shift) {

        word_idx_t totalWordDiscounter = wordCount;
        auto wordDiscounter = wordIdx2wordCountMap;
        while(chain.size())
            chain.pop();
        
        for(str_pos_t wordPos=shift; wordPos<wordsEntryMap.size(); wordPos+=wordSize) {

            word_idx_t wordIdx = wordsEntryMap[wordPos];
            if(wordIdx < 0) {
                
                while(chain.size())
                    chain.pop();
                wordDiscounter = wordIdx2wordCountMap;
                totalWordDiscounter = wordCount;
                continue;
            }

            if(wordDiscounter[wordIdx] == 0) {

                word_idx_t removedWordIdx;
                do {

                    removedWordIdx = chain.front();
                    chain.pop();
                    ++wordDiscounter[removedWordIdx];
                    ++totalWordDiscounter;
                }
                while(removedWordIdx != wordIdx);
            }
            --wordDiscounter[wordIdx];
            --totalWordDiscounter;
            chain.push(wordIdx);

            if(totalWordDiscounter == 0) {

                result.push_back(wordPos - wordSize * (wordCount - 1));

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
    vector<int> answer;

    for(auto it : jsonInput) {

        LOG << "==========";

        it["words"].get_to(words);
        it["str"].get_to(longString);
        it["answer"].get_to(answer);

        vector<int> result = timingRunner<vector<int>, string, vector<string>&>(
            &Solution::findConcatSubstrList,
            longString,
            words
        );

        sort(result.begin(), result.end());

        LOGV(longString);
        LOGV(words);
        LOGV(answer);
        LOGV(result);
        LOGV(result == answer ? "PASSED" : "FAILED");
        printDuration();

        continue;

        auto outputJson = json(result);
        auto ofs = ofstream("./" TEST_OUTPUT);
        ofs << outputJson;
        ofs.close();
    }

    return 0;
}
#endif
