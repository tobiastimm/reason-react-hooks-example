[@bs.val] external token: string = "process.env.API_TOKEN";

[@bs.val] external uri: string = "process.env.API_ENDPOINT";

let inMemoryCache = ApolloInMemoryCache.createInMemoryCache();
let contextHandler = () => {
  let headers = {
    "headers": {
      "authorization": {j|Bearer $token|j},
    },
  };
  headers;
};

let authLink = ApolloLinks.createContextLink(contextHandler);

let httpLink = ApolloLinks.createHttpLink(~uri, ());

let instance =
  ReasonApollo.createApolloClient(
    ~link=ApolloLinks.from([|authLink, httpLink|]),
    ~cache=inMemoryCache,
    (),
  );