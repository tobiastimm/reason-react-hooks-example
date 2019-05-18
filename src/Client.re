let inMemoryCache = ApolloInMemoryCache.createInMemoryCache();

let contextHandler = () => {
  let token = "eyJ0eXAiOiJKV1QiLCJhbGciOiJIUzI1NiJ9.eyJ2ZXJzaW9uIjoxLCJ0b2tlbklkIjoiNjI3Y2FkZGUtMjVkYy00MzZhLTlhMmYtZmMzMWY3OWY0YTYxIn0.L-90eKbtVaZG0JBnRWx85BIqJc9_Af3PRtMbTL1Fshg";
  let headers = {
    "headers": {
      "authorization": {j|Bearer $token|j},
    },
  };
  headers;
};

let authLink = ApolloLinks.createContextLink(contextHandler);

let httpLink =
  ApolloLinks.createHttpLink(
    ~uri="https://api-euwest.graphcms.com/v1/cjvtuzuav5tux01etrbx95u65/master",
    (),
  );

let instance =
  ReasonApollo.createApolloClient(
    ~link=ApolloLinks.from([|authLink, httpLink|]),
    ~cache=inMemoryCache,
    (),
  );