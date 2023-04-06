import fs from 'fs';
import { texts, alphabets, patterns, substitutionSymbols } from "./config.js";


fs.rmSync("tests", { recursive: true, force: true });
for (const textSize of texts)
{
    for (const alphabet of alphabets)
    {
        const text = generateText(textSize, alphabet);
        const folder = `tests/${textSize}-${alphabet}`;
        fs.mkdirSync(folder, { recursive: true });
        fs.writeFileSync(`${folder}/text.txt`, text, "utf-8");
        for (const patternSize of patterns)
        {
            for (const substitutionSymbolsAmount of substitutionSymbols)
            {
                const { test, answer } = generatePattern(text, patternSize, substitutionSymbolsAmount);
                const testFolder = `${folder}/patterns-${substitutionSymbolsAmount}/${patternSize}`;
                fs.mkdirSync(testFolder, { recursive: true });
                fs.writeFileSync(`${testFolder}/in.txt`, test, "utf-8");
                fs.writeFileSync(`${testFolder}/out.txt`, answer, "utf-8");
            }
        }
    }
}



function generateText(textSize, alphabet)
{
    return new Array(textSize).fill(undefined).map((_, index) => alphabet[Math.floor(Math.random() * alphabet.length)]).join('');
}
function generatePattern(text, patternSize, substitutionSymbolsAmount)
{
    const startIndex = Math.floor(Math.random() * (text.length - patternSize));
    let pattern = text.substring(startIndex, startIndex + patternSize).split('');
    for (let i = 0; i < substitutionSymbolsAmount; i++)
    {
        const index = Math.floor(Math.random() * pattern.length);
        if (pattern[index] == '?') i--;
        pattern[index] = '?';
    }
    const test = pattern.join('');

    const regex = new RegExp(test.replaceAll("?", "."), "g");
    let answer = [ ], match;
    while (match = regex.exec(text))
    {
        answer.push(match.index);
        regex.lastIndex = match.index + 1;
    }

    return { test, answer: answer.join(' ') };
}