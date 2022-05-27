const modelModule = require ("./build/Release/model.node")

console.log("exports: ", modelModule)
console.log()

console.log("result: ", modelModule.lemmatizer("свекруха"))