module Styles = {
  open Css;

  let card =
    style([
      display(`flex),
      flexDirection(`column),
      height(rem(30.)),
      width(rem(30.)),
      backgroundColor(hex("fff")),
      `shadow("0 1px 2px rgba(0,0,0,0.12), 0 1px 2px rgba(0,0,0,0.24);"),
    ]);
};

[@react.component]
let make = (~recipe) =>
  <li className=Styles.card>
    <div> {recipe##title |> React.string} </div>
    <div> {React.string("Card")} </div>
  </li>;