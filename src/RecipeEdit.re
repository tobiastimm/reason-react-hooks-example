module Styles = {
  open Css;
};

[@react.component]
let make = () => {
  let (id, setId) = React.useState(() => "");
  let url = ReasonReactRouter.useUrl();
  if (id == "") {
    switch (url.path) {
    | ["recipe", id, "edit"] => setId(_ => id)
    | _ => ()
    };
  };
  <div> {id |> React.string} </div>;
};