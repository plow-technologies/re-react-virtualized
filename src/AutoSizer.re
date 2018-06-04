[@bs.module "react-virtualized"]
external autoSizer : ReasonReact.reactClass = "AutoSizer";

[@bs.deriving abstract]
type params = {
  height: int,
  width: int
};

let make = (~disableHeight=false,
            ~disableWidth=false,
            children) => {
  ReasonReact.wrapJsForReason(
    ~reactClass=autoSizer,
    ~props={
      "disableHeight": disableHeight,
      "disableWidth": disableWidth
    },
    children
  );
}
