function save(path) {
    var tree = readTree()
    var saveFile = {

    }
}

// create unique id for all SynthItems
// needed before reading tree to save session
function setIdentifiers(items) {
    for(var i = 0; i < items.length; i++) {
        var item = items[i]
        item.identifier = i
    }
}

function readTree(items) {
    setIdentifiers(items)
    var synthTree = {};
    var synthItems = []
    synthTree.synthItems = synthItems

    for (var i = 0; i < items.length; i++) {
        var item = items[i]
        var jsonItem = item.read()
        synthTree.synthItems.push(jsonItem)
    }

    return synthTree
}
