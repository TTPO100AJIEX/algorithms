const texts = [ 10000, 100000 ];
const alphabets = [ "01", "abcd" ];
const patterns = [ ];
for (let i = 100; i <= 3000; i += 100) patterns.push(i);
const substitutionSymbols = [ 0, 1, 2, 3, 4 ];

const algorithms = [ /*"naive", "naive-no-break", "kmp", "kmp-optimized", "aho-corasick",*/ "stl" ];
const runs = 50;

export { texts, alphabets, patterns, substitutionSymbols, algorithms, runs };