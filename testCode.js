var exec = require('child_process').exec;
// run my compress on normal command
exec('./MyCompress ./testFiles/testFile.txt ./testFiles/myCompressOutput.txt', function (err, stdout, stderr) {
    console.log('Command ran: ./MyCompress ./testFiles/testFile.txt ./testFiles/myCompressOutput.txt');
    if (err) {
        console.log("stderr:", stderr);
    }
    console.log("output:\n\n", stdout);
});
// run my compress on error condition
exec('./MyCompress ./blah.txt ./output.txt', function (err, stdout, stderr) {
    console.log('Command ran: ./MyCompress ./blah.txt ./blah.txt');
    if (err) {
        console.log("stderr:", stderr);
    }
    console.log("output:\n\n", stdout);
});
// run My Decompress normally
exec('./MyDecompress ./testFiles/testCompressedOutput.txt ./testFiles/myDecompressOutput.txt', function (err, stdout, stderr) {
    console.log('Command ran: ./MyDecompress ./testFiles/testCompressedOutput.txt ./testFiles/myDecompressOutput.txt');
    if (err) {
        console.log("stderr:", stderr);
    }
    console.log("output:\n\n", stdout);
});
// run my Decompress with error condition
// run my compress on error condition
exec('./MyDecompress ./blah.txt ./output.txt', function (err, stdout, stderr) {
    console.log('Command ran: ./MyDecompress ./blah.txt ./blah.txt');
    if (err) {
        console.log("stderr:", stderr);
    }
    console.log("output:\n\n", stdout);
});
// run fork compress normally
exec('./ForkCompress ./testFiles/testFile.txt ./testFiles/forkCompressOutput.txt', function (err, stdout, stderr) {
    console.log('Command ran: ./ForkCompress ./testFiles/testFile.txt ./testFiles/forkCompressOutput.txt');
    if (err) {
        console.log("stderr:", stderr);
    }
    console.log("output:\n\n", stdout);
});
// run fork compress with error
exec('./ForkCompress ./blah.txt ./output.txt', function (err, stdout, stderr) {
    console.log('Command ran: ./ForkCompress ./blah.txt ./blah.txt');
    if (err) {
        console.log("stderr:", stderr);
    }
    console.log("output:\n\n", stdout);
});
// run pipe compress normally
exec('./PipeCompress ./testFiles/testFile.txt ./testFiles/PipeCompressOutput.txt', function (err, stdout, stderr) {
    console.log('\nCommand ran: ./PipeCompress ./testFiles/testFile.txt ./testFiles/myPipeCompressOutput.txt');
    if (err) {
        console.log("stderr:\n", stderr);
    }
    console.log("output:\n\n", stdout);
});
// run pipe compress with error
exec('./PipeCompress ./blah.txt ./output.txt', function (err, stdout, stderr) {
    console.log('Command ran: ./PipeCompress ./testFiles/testFile.txt ./testFiles/myPipeCompressOutput.txt');
    if (err) {
        console.log("stderr:", stderr);
    }
    console.log("output:\n\n", stdout);
});
// run par fork normally
exec('./ParFork ./testFiles/testFile.txt ./testFiles/ParForkOutput.txt', function (err, stdout, stderr) {
    console.log('\nCommand ran: ./ParFork ./testFiles/testFile.txt ./testFiles/ParForkOutput.txt');
    if (err) {
        console.log("stderr:\n", stderr);
    }
    console.log("output:\n\n", stdout);
});
// run par fork with error
exec('./ParFork ./blah.txt ./output.txt', function (err, stdout, stderr) {
    console.log('\nCommand ran: ./ParFork ./blah.txt ./output.txt');
    if (err) {
        console.log("stderr:\n", stderr);
    }
    console.log("output:\n\n", stdout);
});
// run ParThread
exec('./ParThread ./testFiles/testFile.txt ./testFiles/ParThreadOutput.txt', function (err, stdout, stderr) {
    console.log('\nCommand ran: ./ParThread ./testFiles/testFile.txt ./testFiles/ParThreadOutput.txt');
    if (err) {
        console.log("stderr:\n", stderr);
    }
    console.log("output:\n\n", stdout);
});
// run ParThread with error
exec('./ParThread ./blah.txt ./output.txt', function (err, stdout, stderr) {
    console.log('\nCommand ran: ./ParThread ./blah.txt ./output.txt');
    if (err) {
        console.log("stderr:\n", stderr);
    }
    console.log("output:\n\n", stdout);
});
