import { exec } from 'child_process';

export default async function handler(req, res) {
    if (req.method === 'POST') {
        const { code } = req.body;

        // 将代码写入文件
        const fs = require('fs');
        fs.writeFileSync('temp.cpp', code);

        // 编译代码
        exec('g++ temp.cpp -o temp', (compileError) => {
            if (compileError) {
                return res.status(400).json({ error: '编译错误' });
            }

            // 执行代码
            exec('./temp', (execError, stdout, stderr) => {
                if (execError) {
                    return res.status(400).json({ error: '执行错误' });
                }
                res.status(200).json({ output: stdout });
            });
        });
    } else {
        res.setHeader('Allow', ['POST']);
        res.status(405).end(`Method ${req.method} Not Allowed`);
    }
} 