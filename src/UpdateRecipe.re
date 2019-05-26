module Styles = {
  open Css;

  let container =
    style([
      display(`flex),
      width(pct(100.)),
      justifyContent(`center),
      alignItems(`flexStart),
      padding(rem(10.)),
      gridColumnStart(1),
      gridColumnEnd(3),
    ]);
  let card =
    style([
      display(`flex),
      flexDirection(`column),
      unsafe(
        "box-shadow",
        "0px 1px 3px 0px rgba(0,0,0,0.2), 0px 1px 1px 0px rgba(0,0,0,0.14), 0px 2px 1px -1px rgba(0,0,0,0.12)",
      ),
      borderRadius(px(4)),
      backgroundColor(hex("fff")),
      padding2(~v=rem(2.4), ~h=rem(1.6)),
      minWidth(rem(35.)),
      width(rem(65.)),
      selector(
        "form",
        [
          border(px(5), `solid, hex("fff")),
          padding(rem(2.)),
          fontSize(rem(1.5)),
          fontWeight(`num(600)),
          selector(
            "label",
            [display(`block), margin2(~v=rem(1.), ~h=`zero)],
          ),
          selector(
            "input, textarea, select",
            [
              width(pct(100.)),
              height(px(40)),
              padding(rem(0.5)),
              fontSize(rem(1.6)),
              border(px(1), `solid, hex("000")),
              focus([
                unsafe("outline", "0"),
                borderColor(hex(Theme.colorPink)),
              ]),
            ],
          ),
          selector(
            "button, input[type='submit']",
            [
              marginTop(rem(1.2)),
              cursor(`pointer),
              width(`auto),
              backgroundColor(hex(Theme.colorPink)),
              color(hex("fff")),
              borderWidth(`zero),
              fontSize(rem(2.)),
              fontWeight(`num(600)),
              unsafe("float", "right"),
              padding2(~v=rem(0.5), ~h=rem(1.2)),
              unsafe("transition", "background 250ms ease-in-out 0s"),
              hover([backgroundColor(hex("FF487D"))]),
            ],
          ),
          selector(
            "fieldset",
            [
              borderWidth(`zero),
              padding(`zero),
              disabled([opacity(0.5)]),
            ],
          ),
        ],
      ),
    ]);
};

module GetRecipeById = [%graphql
  {|
    query getRecipeById($id:ID!){
      recipe(where: { id: $id}){
        id
        title
        description
      }
    }
  |}
];

module GetRecipeByIdQuery = ReasonApollo.CreateQuery(GetRecipeById);

[@react.component]
let make = () => {
  let url = ReasonReactRouter.useUrl();

  <div className=Styles.container>
    <div className=Styles.card>
      <form>
        {switch (url.path) {
         | ["recipe", id, "edit"] =>
           let recipeByIdQuery = GetRecipeById.make(~id, ());
           <GetRecipeByIdQuery variables=recipeByIdQuery##variables>
             ...{({result}) =>
               switch (result) {
               | Loading => <div> {React.string("Loading")} </div>
               | Error(error) => <div> {React.string(error##message)} </div>
               | Data(response) =>
                 let recipe =
                   switch (response##recipe) {
                   | Some(recipe) => recipe
                   | None => {"id": "", "title": "", "description": ""}
                   };
                 <fieldset>
                   <label htmlFor="name"> {"Name" |> React.string} </label>
                   <input
                     id="name"
                     name="name"
                     placeholder="Name of the recipe"
                     required=true
                     type_="text"
                     value=recipe##title
                   />
                   <label htmlFor="description">
                     {"Description" |> React.string}
                   </label>
                   <textarea
                     id="description"
                     name="description"
                     placeholder="Description for the recipe"
                     required=true
                     value=recipe##description
                   />
                   <button type_="submit"> {"Submit" |> React.string} </button>
                 </fieldset>;
               }
             }
           </GetRecipeByIdQuery>;
         | _ => <> </>
         }}
      </form>
    </div>
  </div>;
};