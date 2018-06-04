[@bs.module "react-virtualized"]
external windowScroller : ReasonReact.reactClass = "WindowScroller";

[@bs.deriving abstract]
type params = {
  height: int,
  width: int,
  scrollLeft: int,
  scrollTop: int,
  isScrolling: bool,
  onChildScroll: unit => unit,
  registerChild: Js.nullable(Dom.element) => unit
};

/* onChildScroll: ({scrollTop: number}) => void, */
/* registerChild: (?Element) => void, */

let make = (/* scrollElement, */
            children) => {
  ReasonReact.wrapJsForReason(
    ~reactClass=windowScroller,
    ~props={},
    children
  );
}
