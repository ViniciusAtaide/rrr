exception MutationFailed(string);

module Mutation = [%relay.mutation
  {|
    mutation UpdateUserMutation($input: UpdateUserByCpfCnpjInput!) {
      updateUserByCpfCnpj(input: $input) {
        user {
          _id
        }
      }
    }
  |}
];

let commit = (~environment, ~cpfCnpj, ~email, ~iswhats, ~name, ~phone) => {
  Mutation.commitMutation(
    ~environment,
    ~variables={
      input: {
        clientMutationId: None,
        cpfCnpj,
        userPatch: {
          _id: None,
          cpfCnpj: None,
          name,
          email,
          phone,
          iswhats,
        },
      },
    },
    (),
  );
};