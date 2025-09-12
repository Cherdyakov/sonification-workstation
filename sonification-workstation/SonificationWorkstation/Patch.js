.pragma library

class Patch {
  constructor(parent, child) {
    this.parent = parent;
    this.child = child;
  }

  // Custom equality method
  equals(otherPatch) {
    if (!(otherPatch instanceof Patch)) {
      return false; // Not a Point object
    }
    return this.parent === otherPatch.parent && this.child === otherPatch.child;
  }

}
