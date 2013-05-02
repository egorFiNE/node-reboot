
// boys stop here
console.log("If this test performs successfully, you would be mad at me :-) So it is disabled.");
process.exit();

// real men get there
var reboot = require('./index.js');
reboot.reboot();
console.log("You are either running as non-root or node no reboot permissions. See README.md for node-reboot.");
