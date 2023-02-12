import fs from 'fs';
import excelJS from 'exceljs';
import timeData from "../report/data/COUNT_TIME.json" assert { type: "json" };
import opsData from "../report/data/COUNT_ELEMENTARY_OPERATIONS.json" assert { type: "json" };
import { groups, runs } from './config.js';

let workbook = new excelJS.Workbook(), object = { };
function addSheet(workbook = new excelJS.Workbook(), object, name, data)
{
    const localRuns = (name == 'time') ? runs : 1;
    object[name] = { };
    let worksheet = workbook.addWorksheet(name), nextRow = 1, columns = groups.reduce((prev, cur) => prev + cur.length, 0);
    for (const algorithm in data)
    {
        object[name][algorithm] = new Array(data[algorithm].length);
        
        worksheet.mergeCells(nextRow, 2, nextRow, columns + 1);
        let heading = worksheet.getRow(nextRow).getCell(2); heading.value = algorithm; heading.alignment = { vertical: "middle" }; heading.font = { size: 24, bold: true };
        worksheet.getRow(nextRow).height = 30;

        for (let groupIndex = 0, column = 2; groupIndex < data[algorithm].length; groupIndex++)
        {
            const group = data[algorithm][groupIndex];
            object[name][algorithm][groupIndex] = { };

            worksheet.mergeCells(nextRow + 1, column, nextRow + 1, column + group.length - 1);
            let subheading = worksheet.getRow(nextRow + 1).getCell(column); subheading.value = `Group ${groupIndex + 1}`; subheading.alignment = { vertical: "middle" }; subheading.font = { size: 18, bold: true };
            worksheet.getRow(nextRow + 1).height = 25;

            for (let runIndex = 0; runIndex < group[0].length; runIndex++)
            {
                let runCell = worksheet.getRow(nextRow + runIndex + 3).getCell(1); runCell.value = `Запуск ${runIndex + 1}`; runCell.alignment = { vertical: "middle" }; runCell.font = { size: 12, bold: true };
            }
            worksheet.getColumn("A").width = 12;
            for (let testIndex = 0; testIndex < group.length; testIndex++)
            {
                const test = group[testIndex];
                const [ size, type ] = fs.readFileSync(`tests/group${groupIndex + 1}/test${testIndex + 1}/descirption.txt`, "utf-8").split(' ');
                object[name][algorithm][groupIndex][type] ??= { };
                object[name][algorithm][groupIndex][type][size] = test.reduce((prev, cur) => prev + cur, 0) / test.length;

                let head = worksheet.getRow(nextRow + 2).getCell(column + testIndex); head.value = `Test ${testIndex + 1}`; head.alignment = { vertical: "middle", horizontal: "center" }; head.font = { size: 12, bold: true };
                for (let resultIndex = 0; resultIndex < test.length; resultIndex++) { let resultCell = worksheet.getRow(nextRow + resultIndex + 3).getCell(column + testIndex); resultCell.value = test[resultIndex]; resultCell.alignment = { vertical: "middle", horizontal: "center" }; resultCell.font = { size: 10 }; }
            }
            
            column += group.length;
        }

        worksheet.getRow(nextRow + 2).height = 20;
        for (let rowIndex = nextRow + 3; rowIndex < nextRow + localRuns; rowIndex++) worksheet.getRow(rowIndex).height = 15;

        worksheet.mergeCells(nextRow + localRuns + 3, 1, nextRow + localRuns + 3, columns + 1);
        worksheet.getRow(nextRow + localRuns + 3).getCell(1).fill = { type: "pattern", pattern: "solid", bgColor: { argb: 'FF000000' } };
        worksheet.getRow(nextRow + localRuns + 3).height = 10;
        nextRow += localRuns + 4;
    }
}
addSheet(workbook, object, "time", timeData);
addSheet(workbook, object, "operations", opsData);
await workbook.xlsx.writeFile("report/data/raw.xlsx");
fs.writeFileSync("report/data/data.json", JSON.stringify(object, null, 4), "utf-8");