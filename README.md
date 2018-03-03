# node-win-extracticon

A small plugin that let you extract an associated icon from a file. The icon extracted is large and contains transparency.
The plugin let you display a list of file using OS file system icons.
It only works with windows OS.

## Usage

```
npm i --save node-win-extracticon
```


```javascript
getIcon(path.resolve("./donotexists"), "test/donotexists.ico", function (err,msg) {
    console.log(msg);
})
```

Typescript definition
```typescript
declare module exicon{
    export function getIcon(src: string, dest: string, callback: (err:Error,path:string) => void) ;
}
```

See demo folder!