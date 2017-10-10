function itemsRect(items) {

    var xMax = 0
    var yMax = 0

    if(items.length > 0) {

        var item = items[0]

        xMax = item.x
        yMax = item.y

        for(var i = 1; i < items.length; i++) {
            item = items[i]
            if(item.x > xMax) {
                xMax = item.x
            }
            if(item.y > yMax) {
                yMax = item.y
            }
        }
    }

    return {
        xMax: xMax,
        yMax: yMax
    }
}
