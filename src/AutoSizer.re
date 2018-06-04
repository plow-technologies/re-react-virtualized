[@bs.module "react-virtualized"]
external autoSizer : ReasonReact.reactClass = "AutoSizer";

[@bs.deriving abstract]
type params = {
  height: int,
  width: int
};

let make = (children) => {
  ReasonReact.wrapJsForReason(
    ~reactClass=autoSizer,
    ~props={},
    children
  );
}
