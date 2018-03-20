# mv-exchange

Simple node.js native addon using n-api which calls renameat2 with exchange flag
set. Why is this useful? I causes two files to swap places atomically so that
there is never one of them missing or both of them containing same data.

# Install

`npm i mv-exchange` or globally with `npm i -g mv-exchange`

# Usage

As module:

```
const mvExchange = require('mv-exchange');
mvExchange('file1', 'file2');
```

Operation is synchronous and throws on failure

Using CLI

```
mv-exchange file1 file2
```

Using npx

```
npx mv-exchange file1 file2
```

# Platform support

This only supports linux with `renameat2` syscall. If you know how to do this on
other platforms open issue with explanation or open pull request.
