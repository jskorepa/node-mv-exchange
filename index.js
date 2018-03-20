const addon = require('bindings')('swap')
const path = require('path')

function exchangeFilesSync(a, b) {
  if (typeof a !== 'string' || typeof b !== 'string')
    throw new Error('Filename must be string')

  if (!path.isAbsolute(a)) {
    a = path.resolve(process.cwd(), a)
  }
  if (!path.isAbsolute(b)) {
    b = path.resolve(process.cwd(), b)
  }

  const ret = addon.swap(
    path.dirname(a),
    path.basename(a),
    path.dirname(b),
    path.basename(b),
  )
  if (ret !== '') {
    throw new Error(ret + `: Exchanging files failed, exchange '${a}' '${b}'`)
  }
}
module.exports = exchangeFilesSync
