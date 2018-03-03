if (process.platform === 'win32') {
    let addon = null;
    try {
        addon = require('./build/Release/exicon.node');
    } catch (err) {
        addon = require('./build/Debug/exicon.node');
    }
    exports.getIcon = addon.getIcon;
}