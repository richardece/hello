// To run
// $ node index.js
//Since index.js is the default entry point, we can just say
// $ node .
function sayHello (name) {
    console.log('Hello ' + name);
}

sayHello('Richard');
console.log(process.platform);

//===================Events and callback
//Example 1
//When a node process exits, it emits an exit event.
//We listen to exit event and call the callback
process.on('exit', function(){
    console.log('node exit');
})

// Example2
//Import event emitter from events module
const { EventEmitter } = require('events');
//Instantiate a new event emitter
const eventEmitter = new EventEmitter();
//Declare the event and corresponding event handler
eventEmitter.on('lunch', () => {
    console.log('yum')
})
//Emit the signal twice
eventEmitter.emit('lunch')
eventEmitter.emit('lunch')


//===================Filesystem


//===================Modules
//discuss npm to manage dependencies

 
