package main

import (
	"bufio"
	"fmt"
	"os"
    "io"
    "regexp"
    "strings"
    "log"
    "math"
    "math/big"
)

func getWordFreq(fileName string) map[string]int {
	fl, flErr := os.Open(fileName)
	defer fl.Close()
	if flErr != nil {
		log.Fatal("open:", flErr)
	}

	var line string
    var numWords int
    var numLines int = 0

	rd := bufio.NewReader(fl)
	var rdErr error
    var words []string
    wordFreq := make(map[string]int)
	for rdErr == nil {
		line, rdErr = rd.ReadString('\n')
        if (rdErr != io.EOF && rdErr != nil) {
            panic(rdErr)
        } else if (rdErr != io.EOF) {
            numLines = numLines + 1
            if len(line) > 0 {
                words = regexp.MustCompile("[^A-Za-z0-9]+").Split(line, -1)
                if (len(words) > 0) {
                    numWords = numWords + len(words)
                }
                for _,word := range words {
                    if (len(word) > 0) {
                        wordFreq[strings.ToLower(word)] = wordFreq[strings.ToLower(word)] + 1
                    }
                }
            }
        }
	}
    fmt.Printf("The no of words are %d and lines are %d and distinct words are %d\n",numWords,numLines,len(wordFreq))
    return wordFreq
}

func innerProduct(vector1 map[string]int, vector2 map[string]int) int64 {
    var product int64 = 0
    for word := range vector1 {
        _, present := vector2[word]
        if (present) {
            product = product + int64(vector1[word] * vector2[word])
        }
    }
    fmt.Printf("Product is %d\n",product)
    return product
}

func main() {
	if (len(os.Args) < 3) {
        log.Fatal("Please supply at least two file names")
        return
    } else {
        wordsFile1 := getWordFreq(os.Args[1])
        wordsFile2 := getWordFreq(os.Args[2])
        numerator := float64(innerProduct(wordsFile1,wordsFile2))
        var partialAns float64 = numerator/math.Sqrt(float64(innerProduct(wordsFile1,wordsFile1))) 
        var Ans float64 = partialAns/math.Sqrt(float64(innerProduct(wordsFile2,wordsFile2)))
        fmt.Printf("The ans is %f\n",Ans)
        fmt.Printf("The distance between the documents is %g\n",math.Acos(Ans))
        return
    }
}
