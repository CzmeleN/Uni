function Tree(val, left, right) {
    this.left = left;
    this.right = right;
    this.val = val;
}

// Tree.prototype[Symbol.iterator] = function*() {
//     yield this.val;
//     if ( this.left ) yield* this.left;
//     if ( this.right ) yield* this.right;
// }

Tree.prototype[Symbol.iterator] = function*() {
    const queue = [this];

    while (queue.length > 0) {
        let first = queue.splice(0, 1)[0];
        // let first = queue.pop(); // dla stosu mamy DFS
        if (first.right) queue.push(first.right);
        if (first.left) queue.push(first.left);
        yield first.val;
    }
}

var root = new Tree( 1, new Tree( 2, new Tree( 3 ) ), new Tree( 4 ));

for ( var e of root ) {
    console.log( e );
}
