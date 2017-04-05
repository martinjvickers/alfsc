/*
KAST - 
Version 0.0.7
Written by Dr. Martin Vickers

MIT License

Copyright (c) 2016 Martin James Vickers

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
 */

#include "distance.h"
#include "utils.h"

/*
Manhattan 0.63265
Ch 0.03061
*/



int testd2star(){

        int klen = 3;
        int markovOrder = 1;
        IupacString qryseq = doRevCompl("AGGCAGCGTACGAACCTACTGGAGTTGCGGTATGGGACCAGGCGACCTCTGATGCAGAGATACAGGAGCGCCGCGCCGGGTCTTCCTTGTAGAAGTCCTG");
        IupacString refseq = doRevCompl("CGGAGACCTCCGTGGACGGGGAAGTCCTGCGCGGGTCAGACGTACGCCCCGATTAGTTGCCCGGACGCCCGGTTGGCAGAAGTGACGGCGACTGCCCTCA");

        ModifyStringOptions options;
        options.klen = klen;
        options.markovOrder = markovOrder;
        map<string, unsigned int> refcounts = count(refseq, klen);
        map<string, unsigned int> querycounts = count(qryseq, klen);
        map<string, bool> ourkmers = makecomplete(options);
        map<string, double> refmarkov = markov(klen, refseq, markovOrder, ourkmers);
        map<string, double> querymarkov = markov(klen, qryseq, markovOrder, ourkmers);

        double dist = d2star(options, ourkmers, refcounts, refmarkov, querycounts, querymarkov);
        double expected = 0.4027100011247771;

        double epsilon = 0.000001;
        if(abs(dist - expected) < epsilon)
        {
                return 0;
        } else {
                printf("Test Euler FAILED: Value expected=%1.15f, but recieved=%1.15f \n", expected, dist);
                return 1;
        }

        return 0;
}

int testd2s(){

        int klen = 3;
	int markovOrder = 1;
        IupacString qryseq = doRevCompl("AGGCAGCGTACGAACCTACTGGAGTTGCGGTATGGGACCAGGCGACCTCTGATGCAGAGATACAGGAGCGCCGCGCCGGGTCTTCCTTGTAGAAGTCCTG");
        IupacString refseq = doRevCompl("CGGAGACCTCCGTGGACGGGGAAGTCCTGCGCGGGTCAGACGTACGCCCCGATTAGTTGCCCGGACGCCCGGTTGGCAGAAGTGACGGCGACTGCCCTCA");

        ModifyStringOptions options;
	options.klen = klen;
	options.markovOrder = markovOrder;
        map<string, unsigned int> refcounts = count(refseq, klen);
        map<string, unsigned int> querycounts = count(qryseq, klen);
	map<string, bool> ourkmers = makecomplete(options);
	map<string, double> refmarkov = markov(klen, refseq, markovOrder, ourkmers);
	map<string, double> querymarkov = markov(klen, qryseq, markovOrder, ourkmers);

	double dist = d2s(options, ourkmers, refcounts, refmarkov, querycounts, querymarkov);
        double expected = 0.432463894423;
	
        double epsilon = 0.000001;
        if(abs(dist - expected) < epsilon)
        {
                return 0;
        } else {
                printf("Test Euler FAILED: Value expected=%1.15f, but recieved=%1.15f \n", expected, dist);
                return 1;
        }

        return 0;
}

int testchebyshev(){

        int klen = 3;
        IupacString qryseq = doRevCompl("AGGCAGCGTACGAACCTACTGGAGTTGCGGTATGGGACCAGGCGACCTCTGATGCAGAGATACAGGAGCGCCGCGCCGGGTCTTCCTTGTAGAAGTCCTG");
        IupacString refseq = doRevCompl("CGGAGACCTCCGTGGACGGGGAAGTCCTGCGCGGGTCAGACGTACGCCCCGATTAGTTGCCCGGACGCCCGGTTGGCAGAAGTGACGGCGACTGCCCTCA");

        ModifyStringOptions options;
        map<string, unsigned int> refcounts = count(refseq, klen);
        map<string, unsigned int> querycounts = count(qryseq, klen);

        double dist = chebyshev(options, refcounts, querycounts);
        double expected = 0.03061;
        double epsilon = 0.00001;
        if(abs(dist - expected) < epsilon)
        {
                return 0;
        } else {
                printf("Test Chebyshev FAILED: Value expected=%1.15f, but recieved=%1.15f \n", expected, dist);
                return 1;
        }

        return 0;
}


int testeuler(){

	int klen = 3;
	IupacString qryseq = doRevCompl("AGGCAGCGTACGAACCTACTGGAGTTGCGGTATGGGACCAGGCGACCTCTGATGCAGAGATACAGGAGCGCCGCGCCGGGTCTTCCTTGTAGAAGTCCTG");
	IupacString refseq = doRevCompl("CGGAGACCTCCGTGGACGGGGAAGTCCTGCGCGGGTCAGACGTACGCCCCGATTAGTTGCCCGGACGCCCGGTTGGCAGAAGTGACGGCGACTGCCCTCA");

	ModifyStringOptions options;
	map<string, unsigned int> refcounts = count(refseq, klen);
	map<string, unsigned int> querycounts = count(qryseq, klen);
	
	double dist = euler(options, refcounts, querycounts);
	double expected = 0.103056;
	double epsilon = 0.000001;
	if(abs(dist - expected) < epsilon)
        {
                return 0;
        } else {
                printf("Test Euler FAILED: Value expected=%1.15f, but recieved=%1.15f \n", expected, dist);
                return 1;
        }

	return 0;
}

int testd2(){

        int klen = 3;
        IupacString qryseq = doRevCompl("AGGCAGCGTACGAACCTACTGGAGTTGCGGTATGGGACCAGGCGACCTCTGATGCAGAGATACAGGAGCGCCGCGCCGGGTCTTCCTTGTAGAAGTCCTG");
        IupacString refseq = doRevCompl("CGGAGACCTCCGTGGACGGGGAAGTCCTGCGCGGGTCAGACGTACGCCCCGATTAGTTGCCCGGACGCCCGGTTGGCAGAAGTGACGGCGACTGCCCTCA");

        ModifyStringOptions options;
        map<string, unsigned int> refcounts = count(refseq, klen);
        map<string, unsigned int> querycounts = count(qryseq, klen);

        double dist = d2(options, refcounts, querycounts);
	double expected = 0.10619;
	double epsilon = 0.000001;
	if(abs(dist - expected) < epsilon)
	{
		return 0;
	} else {
		printf("Test d2 FAILED: Value expected=%1.15f, but recieved=%1.15f \n", expected, dist);
		return 1;
	}

	return 0;
}

int testmanhattan(){

        int klen = 3;
        IupacString qryseq = doRevCompl("AGGCAGCGTACGAACCTACTGGAGTTGCGGTATGGGACCAGGCGACCTCTGATGCAGAGATACAGGAGCGCCGCGCCGGGTCTTCCTTGTAGAAGTCCTG");
        IupacString refseq = doRevCompl("CGGAGACCTCCGTGGACGGGGAAGTCCTGCGCGGGTCAGACGTACGCCCCGATTAGTTGCCCGGACGCCCGGTTGGCAGAAGTGACGGCGACTGCCCTCA");

        ModifyStringOptions options;
        map<string, unsigned int> refcounts = count(refseq, klen);
        map<string, unsigned int> querycounts = count(qryseq, klen);

        double dist = manhattan(options, refcounts, querycounts);
	double expected = 0.63265;
	double epsilon = 0.000001;

	if(abs(dist - expected) < epsilon)
        {
		printf("Test Manhattan PASSED: Value expected=%1.15f, but recieved=%1.15f \n", expected, dist);
                return 0;
        } else {
		printf("Test Manhattan FAILED: Value expected=%1.15f, but recieved=%1.15f \n", expected, dist);
                return 1;
        }

        return 0;
}


int testCount_1()
{
        IupacString seq = "NTGACTGACTGACTGACTGACTGACTGACTGACN";
        int klen = 3;
        map<string, unsigned int> counts = count(seq, klen);

        for(pair<string, unsigned int> p: counts)
        {
                if(p.first == "TGA" && p.second != 8)
                {
                        cout << "TGA should occur 8 times in str: " << seq << " but it's being counted " << p.second << " times." << endl;
                        return 1;
                }
                else if(p.first == "GAC" && p.second != 8)
                {
                        cout << "GAC should occur 8 times in str: " << seq << " but it's being counted " << p.second << " times." << endl;
                        return 1;
                }
                else if(p.first == "ACT" && p.second != 7)
                {
                        cout << "ACT should occur 7 times in str: " << seq << " but it's being counted " << p.second << " times." << endl;
                        return 1;
                }
                else if(p.first == "CTG" && p.second != 7)
                {
                        cout << "CTG should occur 7 times in str: " << seq << " but it's being counted " << p.second << " times." << endl;
                        return 1;
                }
                else if(p.first != "GAC" && p.first != "TGA" && p.first != "ACT" && p.first != "CTG")
                {
                        cout << "We have an unknown 3mer in this test: " << p.first << endl;
			return 1;
                }
        }

        return 0;
}


/*Simple test of reverse compliment*/
int testRevCompl_1()
{
        Dna5String input_dnaSeq = "TGAC";
	Dna5String expected_output_dnaSeq = "TGACNNNGTCA";
        Dna5String recieved_output_dnaSeq = doRevCompl(input_dnaSeq);
	if(expected_output_dnaSeq == recieved_output_dnaSeq)
	{
		return 0;
	} else {
		cout << "Test reverse compliment FAILED: Sent " << input_dnaSeq << " expected " << expected_output_dnaSeq << " recieved " << recieved_output_dnaSeq << endl;
		return 1;
	}
}

//check that when you give it something, it returns what you want
int testRevCompl_2()
{
	if(getRevCompl('A') != 'T')
	{
		cout << "ERROR submitted A but got " << getRevCompl('A') << endl;
		return 1;
	}

	if(getRevCompl('T') != 'A')
        {
                cout << "ERROR submitted T but got " << getRevCompl('T') << endl;
		return 1;
        }

	if(getRevCompl('C') != 'G')
        {
                cout << "ERROR submitted C but got " << getRevCompl('C') << endl;
		return 1;
        }

	if(getRevCompl('G') != 'C')
        {
                cout << "ERROR submitted G but got " << getRevCompl('G') << endl;
		return 1;
        }

	if(getRevCompl('N') != 'N')
        {
                cout << "ERROR submitted N but got " << getRevCompl('N') << endl;
		return 1;
        }
	if(getRevCompl('M') != 'N')
	{
		cout << "ERROR submitted M but got " << getRevCompl('M') << endl;
		return 1;
	}
	if(getRevCompl('X') != 'N')
        {
                cout << "ERROR submitted X but got " << getRevCompl('X') << endl;
		return 1;
        }

	return 0 ;

}

int main(int argc, char const ** argv)
{
	int returncode = 0;

	//testing reverse compliments
	if(testRevCompl_1() != 0)
	{
		returncode = 1;
	} 
	else 
	{
		cout << "Test reverse compliment PASSED" << endl;
	}

	if(testRevCompl_2() != 0)
	{
                returncode = 1;
        }
        else
        {
		cout << "Test Single Base getRevCompl PASSED" << endl;
        }

	//test counting
	if(testCount_1() != 0)
	{
                returncode = 1;
        }
        else
        {
		cout << "Test Count PASSED" << endl;
        }

	//test distances
	if(testeuler() != 0)
        {
                returncode = 1;
        }
        else
        {
                cout << "Test Euler PASSED" << endl;
        }

        if(testd2() != 0)
        {
                returncode = 1;
        }
        else
        {
                cout << "Test d2 PASSED" << endl;
        }

        if(testmanhattan() != 0)
        {
                returncode = 1;
        }
        else
        {
                cout << "Test Manhattan PASSED" << endl;
        }

	if(testd2s() != 0)
        {
                returncode = 1;
        }
        else
        {
                cout << "Test d2s PASSED" << endl;
        }

	if(testd2star() != 0)
        {
                returncode = 1;
        }
        else
        {
                cout << "Test d2star PASSED" << endl;
        }

	if(testchebyshev() != 0)
        {
                returncode = 1;
        }
        else
        {
                cout << "Test Chebyshev PASSED" << endl;
        }

	return returncode;
}
