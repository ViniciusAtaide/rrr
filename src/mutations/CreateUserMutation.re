exception MutationFailed(string);

module Mutation = [%relay.mutation
  {|
    mutation CreateUserMutation($input: CreateUserInput!) {
      createUser(input: $input) {
        userEdge {
          node {
            name
            _id
            email
            nodeId
          }
        }
      }
    }
  |}
];

let sharedUpdater = (~store, ~newEdge) => {
  ReasonRelay.(
    switch (
      newEdge->RecordProxy.getLinkedRecord(~name="node", ~arguments=None)
    ) {
    | Some(linked) =>
      switch (
        store->RecordSourceSelectorProxy.get(
          ~dataId=linked->RecordProxy.getDataId,
        )
      ) {
      | Some(node) =>
        ReasonRelayUtils.createAndAddEdgeToConnections(
          ~store,
          ~node,
          ~connections=[{parentID: storeRootId, key: "HomeQuery_allUsers"}],
          ~edgeName="userEdge",
          ~insertAt=Start,
        )
      | None => ()
      }

    | None => ()
    }
  );
};

let tempID = ref(0);

let incrementTempId = () => tempID := tempID^ + 1;

let commit = (~environment, ~name, ~email, ~navigation) => {
  Mutation.commitMutation(
    ~environment,
    ~variables={
      input: {
        clientMutationId: None,
        user: {
          _id: None,
          name,
          email,
          cpfCnpj: "",
        },
      },
    },
    ~updater=
      (store, _response) => {
        ReasonRelayUtils.(
          switch (
            resolveNestedRecord(
              ~rootRecord=
                store->ReasonRelay.RecordSourceSelectorProxy.getRootField(
                  ~fieldName="createUser",
                ),
              ~path=["userEdge"],
            )
          ) {
          | Some(newEdge) => sharedUpdater(~store, ~newEdge)
          | None => ()
          }
        )
      },
    ~optimisticUpdater=
      store => {
        open ReasonRelay;

        incrementTempId();

        let id = "client:newUser" ++ string_of_int(tempID^);

        let node =
          store->RecordSourceSelectorProxy.create(
            ~dataId=makeDataId(id),
            ~typeName="User",
          );

        node
        ->RecordProxy.setValueString(
            ~value=name,
            ~name="name",
            ~arguments=None,
          )
        ->RecordProxy.setValueString(~value=id, ~name="_id", ~arguments=None)
        ->ignore;

        let newEdge =
          store->RecordSourceSelectorProxy.create(
            ~dataId=makeDataId("client:newEdge:" ++ string_of_int(tempID^)),
            ~typeName="UserEdge",
          );

        newEdge
        ->RecordProxy.setLinkedRecord(
            ~record=node,
            ~name="node",
            ~arguments=None,
          )
        ->ignore;

        sharedUpdater(~store, ~newEdge);
        navigation->RootNavigator.Navigation.navigate("Home");
      },
    (),
  );
};