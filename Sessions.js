function save(path) {
    var tree = readTree()
    var saveFile = {

    }
}

function readTree(items) {
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
