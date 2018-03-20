#!/usr/bin/env node

if (process.argv.length !== 4) {
  console.error('Usage: mv-exchange file1 file2')
  process.exit(1)
}

const path = require('path')

require('child_process').spawnSync(
  process.argv[0],
  [
    '--no-warnings',
    '--napi-modules',
    path.join(__dirname, 'mv-exchange-impl.js'),
    process.argv[2],
    process.argv[3],
  ],
  {
    stdio: 'inherit',
  },
)
