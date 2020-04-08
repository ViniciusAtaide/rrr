exception MutationFailed(string);

module Mutation = [%relay.mutation
  {|
    mutation CreateUserMutation($input: CreateUserInput!) {
      createUser(input: $input) {
        user {
          _id
        }
      }
    }
  |}
];

let commit = (~environment, ~cpfCnpj) => {
  Mutation.commitMutation(
    ~environment,
    ~variables={
      input: {
        clientMutationId: None,
        user: {
          _id: None,
          name: None,
          email: None,
          phone: None,
          iswhats: None,
          cpfCnpj,
        },
      },
    },
    (),
  );
};