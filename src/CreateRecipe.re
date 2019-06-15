exception GraphQLErrors(array(ReasonApolloTypes.graphqlError));
exception EmptyResponse;

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

module CreateRecipe = [%graphql
  {|
    mutation CreateRecipe($title: String!, $description: String!){
      createRecipe(data: { title: $title, description: $description}) {
        id
      }
    }
  |}
];

module CreateRecipeMutation = ReasonApollo.CreateMutation(CreateRecipe);

type inputValue =
  | Number(float)
  | String(string);

[@react.component]
let make = () => {
  let initialState: list((string, inputValue)) = [];
  let (formState, setFormState) = React.useState(() => initialState);

  let handleChange = (event: ReactEvent.Form.t) => {
    let target = event->ReactEvent.Form.target;
    let value =
      switch (target##_type, target##value) {
      | ("number", value) => Number(float_of_string(value))
      | (_, value) => String(value)
      };
    setFormState(prevFormState =>
      if (Util.containsKey(~value=target##name, prevFormState)) {
        Util.replaceKey(
          ~key=target##name,
          ~with_=(target##name, value),
          prevFormState,
        );
      } else {
        [(target##name, value), ...prevFormState];
      }
    );
  };
  let rec getValueByKey =
          (~key: 'a, ~default: 'a, l: list((string, inputValue))) => {
    switch (l) {
    | [] => default
    | [(headKey, headValue), ...tail] =>
      if (headKey == key) {
        switch (headValue) {
        | Number(number) => Js.Float.toString(number)
        | String(value) => value
        };
      } else {
        getValueByKey(~key, ~default, tail);
      }
    };
  };

  <div className=Styles.container>
    <div className=Styles.card>
      {<CreateRecipeMutation>
         ...{(mutation, _) => {
           let createRecipeQuery =
             CreateRecipe.make(
               ~title=getValueByKey(~key="name", ~default="", formState),
               ~description=
                 getValueByKey(~key="description", ~default="", formState),
               (),
             );
           <form
             onSubmit={(e: ReactEvent.Form.t) => {
               ReactEvent.Form.preventDefault(e);
               mutation(
                 ~variables=createRecipeQuery##variables,
                 ~refetchQueries=[|"getRecipes"|],
                 (),
               )
               |> Js.Promise.then_(res =>
                    switch (
                      (
                        res:
                          ReasonApolloTypes.executionResponse(CreateRecipe.t)
                      )
                    ) {
                    | Data(_) =>
                      ReasonReactRouter.push("/");
                      Js.Promise.resolve();
                    | Errors(error) =>
                      Js.log(error);
                      Js.Promise.reject(raise(GraphQLErrors(error)));
                    | EmptyResponse =>
                      Js.Promise.reject(raise(EmptyResponse))
                    }
                  )
               |> ignore;
             }}>
             <fieldset>
               <label htmlFor="name"> {"Name" |> React.string} </label>
               <input
                 id="name"
                 name="name"
                 placeholder="Name of the recipe"
                 required=true
                 type_="text"
                 value={getValueByKey(~key="name", ~default="", formState)}
                 onChange=handleChange
               />
               <label htmlFor="description">
                 {"Description" |> React.string}
               </label>
               <textarea
                 id="description"
                 name="description"
                 placeholder="Description for the recipe"
                 required=true
                 value={getValueByKey(
                   ~key="description",
                   ~default="",
                   formState,
                 )}
                 onChange=handleChange
               />
               <button type_="submit"> {"Submit" |> React.string} </button>
             </fieldset>
           </form>;
         }}
       </CreateRecipeMutation>}
    </div>
  </div>;
};