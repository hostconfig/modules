// addon.node plugin file without the extension:
const addon = require('./build/Release/addon');

console.log(addon.hello());

module.exports = addon; // Just reexport it
