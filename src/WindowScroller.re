[@bs.module "react-virtualized"]
external windowScroller : ReasonReact.reactClass = "WindowScroller";

[@bs.deriving abstract]
type params = {
  height: int,
  width: int,
  scrollLeft: int,
  scrollTop: int,
  isScrolling: bool
};

let make = (children) => {
  ReasonReact.wrapJsForReason(
    ~reactClass=windowScroller,
    ~props={},
    children
  );
}
