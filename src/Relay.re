// [@bs.val] external a : () = "react-native-gesture-handler"

exception Graphql_error(string);

let fetchQuery: ReasonRelay.Network.fetchFunctionPromise =
  (operation, variables, _cacheConfig) =>
    Fetch.(
      fetchWithInit(
        "https://mia.adv.br/graphql",
        RequestInit.make(
          ~method_=Post,
          ~body=
            Js.Dict.fromList([
              ("query", Js.Json.string(operation.text)),
              ("variables", variables),
            ])
            |> Js.Json.object_
            |> Js.Json.stringify
            |> BodyInit.make,
          ~headers=
            HeadersInit.make({
              "content-type": "application/json",
              "accept": "application/json",
            }),
          (),
        ),
      )
      |> Js.Promise.(
           then_(resp =>
             if (Response.ok(resp)) {
               Response.json(resp);
             } else {
               ReactNative.ToastAndroid.(
                 showWithGravityAndOffset(
                   "Erro na conexão",
                   long,
                   bottom,
                   ~xOffset=0.,
                   ~yOffset=50.,
                 )
               );

               reject(
                 Graphql_error(
                   "Request failed: " ++ Response.statusText(resp),
                 ),
               );
             }
           )
         )
    );

let network =
  ReasonRelay.Network.makePromiseBased(~fetchFunction=fetchQuery, ());

let environment =
  ReasonRelay.Environment.make(
    ~network,
    ~store=
      ReasonRelay.Store.make(~source=ReasonRelay.RecordSource.make(), ()),
    (),
  );