const debug = require("debug")("events:debug");
const error = require("debug")("events:error");

module.exports = async config => {

    let handlers = {};

    let nextHandlerId = 0;

    function getHandlers(eventName) {
        if (!handlers[eventName]) {
            handlers[eventName] = {};
        }
        return handlers[eventName];
    }

    return {
        on(eventName, handler) {
            let handlerId = nextHandlerId++;
            getHandlers(eventName)[handlerId] = handler;
            return handlerId;
        },

        off(handlerId) {
            delete getHandlers(eventName)[handlerId];
        },

        emit(eventName, ...args) {
            debug(eventName, ...args);
            return Promise.all(Object.values(getHandlers(eventName)).map(handler => {
                async function doAsync() {
                    await handler(...args);
                }
                doAsync().catch(e => error(`Error in event handler ${eventName}:`, e.message || e));
            }));
        }
    }
}