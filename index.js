import modules from './modules.cjs'

console.log(modules.hello());

import express from 'express';

import debugLib from 'debug'
import http from 'http'
// import createError from 'http-errors'
// import { URL } from 'url'
// import path from 'path'
import cookieParser from 'cookie-parser'
import logger from 'morgan'

const app = express();
// view engine setup
app.set('view engine', 'pug')

app.use(logger('dev'))
app.use(express.json())
app.use(express.urlencoded({ extended: false }))
app.use(cookieParser())

app.get('/', (req, res) => {
  res.statusCode = 200;
  res.setHeader('Content-Type', 'text/html');
  res.end(modules.index());
})

app.get('/about', (req, res) => {
  res.statusCode = 200;
  res.setHeader('Content-Type', 'text/html');
  res.end(modules.about());
})

app.get('/favicon.ico', (req, res) => {
  res.statusCode = 200;
  res.setHeader('Content-Type', 'image/x-icon');
  res.end(modules.favicon());
})


const debug = debugLib('hostconfig:modules')

const hostname = '127.0.0.1';
const port = normalizePort(process?.env?.PORT || '3000')

const server = http.createServer(app);

server.listen(port, hostname, () => {
  console.log(`Server running at http://${hostname}:${port}/`);
});

server.on('error', onError)
server.on('listening', onListening)

/**
 * Normalize a port into a number, string, or false.
 */

function normalizePort(val) {
  const port = parseInt(val, 10)

  if (isNaN(port)) {
    // named pipe
    return val
  }

  if (port >= 0) {
    // port number
    return port
  }

  return false
}

/**
 * Event listener for HTTP server "error" event.
 */

function onError(error) {
  if (error.syscall !== 'listen') {
    throw error
  }

  const bind = typeof port === 'string'
    ? 'Pipe ' + port
    : 'Port ' + port

  // handle specific listen errors with friendly messages
  switch (error.code) {
    case 'EACCES':
      console.error(bind + ' requires elevated privileges')
      process.exit(1)
      break
    case 'EADDRINUSE':
      console.error(bind + ' is already in use')
      process.exit(1)
      break
    default:
      throw error
  }
}

/**
 * Event listener for HTTP server "listening" event.
 */

function onListening() {
  const addr = server.address()
  const bind = typeof addr === 'string'
    ? 'pipe ' + addr
    : 'port ' + addr?.port
  debug('Listening on ' + bind)
}

/**
 * Quit on ctrl-c when running docker in terminal
 */

process.on("SIGINT", function onSigint() {
  console.info(
    "Got SIGINT (aka ctrl-c in docker). Graceful shutdown ",
    new Date().toISOString()
  );
  shutdown();
});

/**
 * Quit properly on docker stop
 */

process.on("SIGTERM", function onSigterm() {
  console.info(
    "Got SIGTERM (docker container stop). Graceful shutdown ",
    new Date().toISOString()
  );
  shutdown()
})

/**
 * Shut down server
 */

function shutdown() {
  server.close(function onServerClosed(err) {
    if (err) {
      console.error(err)
      process.exit(1)
    }
    process.exit(0)
  })
}
