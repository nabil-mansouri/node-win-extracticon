const path = require("path")
const fs = require("fs")

if (!fs.existsSync("test")) {
    fs.mkdirSync("test");
}
const getIcon = require("node-win-extracticon").getIcon
getIcon(path.resolve(__dirname, "excel.png"), "test/png.ico", function (err,data) {
    console.log(data);
})
getIcon(path.resolve(__dirname, "package.json"), "test/json.ico", function (err,data) {
    console.log(data);
})
getIcon(path.resolve(__dirname, "index.js"), "test/js.ico", function (err,data) {
    console.log(data);
})
getIcon(path.resolve("./donotexists"), "test/donotexists.ico", function (err,data) {
    console.error(err,data);
})
getIcon(path.resolve("."), "test/folder.ico", function (err,data) {
    console.error(err,data);
})
getIcon("C:\\", "test/root.ico", function (err,data) {
    console.error(err,data);
})