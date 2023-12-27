// addon.node plugin file without the extension:
const addon = require('./build/Release/addon');

console.log(addon.hello());

console.log(addon.funcyfunc());

module.exports = addon; // Just reexport it
