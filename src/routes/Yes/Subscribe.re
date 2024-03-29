module KeyboardHide = {
  [@bs.module "react-native-hide-with-keyboard"] [@react.component]
  external make: (~children: React.element) => React.element = "default";
};

module SubscribeForm = [%form
  {target: ReactNative};
  type input = {
    name: string,
    email: Utils.Email.t,
    phone: string,
    iswhats: bool,
  };
  let validators = {
    name: {
      strategy: OnFirstBlur,
      validate: input =>
        switch (input.name) {
        | "" => Error({j|Nome Obrigatório.|j})
        | _ => Ok(input.name)
        },
    },

    email: {
      strategy: OnFirstBlur,
      validate: input =>
        switch (input.email) {
        | "" => Error({j|Email Obrigatório|j})
        | _ =>
          switch (input.email->Utils.Email.validate) {
          | None => Error({j|Email não formatado|j})
          | Some(_) => Ok(input.email)
          }
        },
    },

    phone: {
      strategy: OnFirstBlur,
      validate: input =>
        switch (input.phone) {
        | "" => Error({j|Telefone Obrigatório|j})
        | _ => Ok(input.phone)
        },
    },

    iswhats: {
      strategy: OnFirstBlur,
      validate: input =>
        switch (input.iswhats) {
        | _ => Ok(input.iswhats)
        },
    },
  }
];

let styles =
  ReactNative.Style.(
    ReactNative.StyleSheet.create({
      "bg": style(~backgroundColor="rgb(36, 37, 36)", ~flex=1., ()),
      "container":
        style(
          ~height=100.->pct,
          ~width=100.->pct,
          ~alignContent=`spaceAround,
          ~padding=25.->dp,
          ~flex=1.,
          (),
        ),
      "wrapper": style(~flex=1., ~justifyContent=`center, ()),

      "txt":
        style(
          ~fontFamily="Montserrat-SemiBold",
          ~color="#fff",
          ~fontSize=22.,
          ~paddingTop=20.->dp,
          (),
        ),
      "txtSmall": style(~fontSize=16., ()),
      "txtBlk":
        style(
          ~fontFamily="Montserrat-Bold",
          ~color="black",
          ~fontSize=24.,
          ~lineHeight=48.,
          (),
        ),
      "txtGray":
        style(
          ~fontFamily="Montserrat-Light",
          ~color="gray",
          ~fontSize=24.,
          ~lineHeight=48.,
          (),
        ),
      "inputWrapper": style(~width=100.->pct, ()),
      "input":
        style(
          ~backgroundColor="#fff",
          ~fontFamily="Montserrat-Regular",
          ~height=40.->dp,
          (),
        ),
      "orange":
        style(
          ~color="rgb(254,80,0)",
          ~fontFamily="Montserrat-Bold",
          ~fontSize=22.,
          (),
        ),

      "button":
        style(
          ~fontFamily="Montserrat-SemiBold",
          ~backgroundColor="#fff",
          ~fontSize=28.,
          ~width=100.->pct,
          ~alignItems=`center,
          (),
        ),
      "buttonWrapper": style(~flex=1., ~justifyContent=`flexEnd, ()),
      "errorMessageText":
        style(
          ~fontSize=16.,
          ~fontFamily="Montserrat-SemiBold",
          ~color="rgb(254,80,0)",
          (),
        ),
      "horizontal": style(~flexDirection=`row, ()),
      "radio":
        style(
          ~backgroundColor="rgb(26,26,25)",
          ~height=40.->dp,
          ~width=40.->dp,
          ~alignItems=`center,
          ~justifyContent=`center,
          ~marginTop=10.->dp,
          ~marginHorizontal=5.->dp,
          ~borderRadius=100.,
          (),
        ),
      "radioActive": style(~backgroundColor="rgb(254,80,0)", ()),
      "txtRadio": style(~marginTop=(-20.)->dp, ()),
    })
  );

[@react.component]
let make =
    (
      ~navigation,
      ~route:
         ReactNavigation.Core.route(
           Navigators.SubscribeNavigator.StakeParams.params,
         ),
    ) => {
  open React;
  open ReactNative;

  let environment = ReasonRelay.useEnvironmentFromContext();

  let emailRef = useRef(Js.Nullable.null);
  let numberRef = useRef(Js.Nullable.null);

  let cpfCnpj =
    route.params->Belt.Option.mapWithDefault("", param => {param.cpfCnpj});

  let form =
    SubscribeForm.useForm(
      ~initialInput={name: "", email: "", phone: "", iswhats: false},
      ~onSubmit=(output, cb) => {
      Js.Promise.(
        UpdateUserMutation.commit(
          ~environment,
          ~cpfCnpj,
          ~name=Some(output.name),
          ~phone=Some(output.phone),
          ~email=Some(output.email),
          ~iswhats=Some(output.iswhats),
        )
        |> then_(_ => {
             navigation->Navigators.SubscribeNavigator.Navigation.navigateWithParams(
               "Options",
               {cpfCnpj: cpfCnpj},
             );
             cb.reset();
             Keyboard.dismiss();
             resolve();
           })
        |> catch(_ => {
             Keyboard.dismiss();
             cb.notifyOnFailure();

             navigation->Navigators.SubscribeNavigator.Navigation.navigateWithParams(
               "Options",
               {cpfCnpj: cpfCnpj},
             );

             resolve();
           })
        |> ignore
      ) 
    });

  <View style={styles##bg}>
    <View style={styles##container}>
      <TouchableWithoutFeedback onPress={_ => Keyboard.dismiss()}>
        <View style={styles##wrapper}>
          <Text style={styles##orange}>
            {j|Vamos conversar?|j}->React.string
          </Text>
          <View style={styles##inputWrapper}>
            <Text style={styles##txt}> "Qual seu nome?"->React.string </Text>
            <TextInput
              returnKeyType=`next
              blurOnSubmit=false
              style={styles##input}
              onChangeText={name =>
                form.updateName(input => {...input, name})
              }
              onSubmitEditing={_ => {
                numberRef
                ->React.Ref.current
                ->Js.Nullable.toOption
                ->Belt.Option.map(number => number->TextInput.focus)
                ->ignore
              }}
            />
            {switch (form.nameResult) {
             | Some(Error(message)) =>
               <View>
                 <Text style={styles##errorMessageText}>
                   message->React.string
                 </Text>
               </View>
             | Some(Ok(_))
             | None => React.null
             }}
          </View>
          <View style={styles##inputWrapper}>
            <Text style={styles##txt}> "Telefone"->React.string </Text>
            <TextInput
              returnKeyType=`next
              style={styles##input}
              blurOnSubmit=false
              ref=numberRef
              keyboardType=`phonePad
              onChangeText={phone =>
                form.updatePhone(input => {...input, phone})
              }
              onSubmitEditing={_ => {
                emailRef
                ->React.Ref.current
                ->Js.Nullable.toOption
                ->Belt.Option.map(email => email->TextInput.focus)
                ->ignore
              }}
            />
            <View style={styles##horizontal}>
              <Text style={Style.array([|styles##txt, styles##txtSmall|])}>
                {j|Aplicativo de Mensagem?|j}->React.string
              </Text>
              <View
                style={Style.listOption([
                  Some(styles##radio),
                  form.input.iswhats ? Some(styles##radioActive) : None,
                ])}>
                <TouchableOpacity
                  onPress={_ =>
                    form.updateIswhats(input => {...input, iswhats: true})
                  }>
                  <Text
                    style={Style.list([
                      styles##txt,
                      styles##txtSmall,
                      styles##txtRadio,
                    ])}>
                    {j|Sim|j}->React.string
                  </Text>
                </TouchableOpacity>
              </View>
              <View
                style={Style.listOption([
                  Some(styles##radio),
                  form.input.iswhats ? None : Some(styles##radioActive),
                ])}>
                <TouchableOpacity
                  onPress={_ =>
                    form.updateIswhats(input => {...input, iswhats: false})
                  }>
                  <Text
                    style={Style.list([
                      styles##txt,
                      styles##txtSmall,
                      styles##txtRadio,
                    ])}>
                    {j|Não|j}->React.string
                  </Text>
                </TouchableOpacity>
              </View>
            </View>
            {switch (form.phoneResult) {
             | Some(Error(message)) =>
               <View>
                 <Text style={styles##errorMessageText}>
                   message->React.string
                 </Text>
               </View>
             | Some(Ok(_))
             | None => React.null
             }}
          </View>
          <View style={styles##inputWrapper}>
            <Text style={styles##txt}> "E-Mail"->React.string </Text>
            <TextInput
              returnKeyType=`go
              style={styles##input}
              ref=emailRef
              keyboardType=`emailAddress
              onChangeText={email =>
                form.updateEmail(input => {...input, email})
              }
            />
            {switch (form.emailResult) {
             | Some(Error(message)) =>
               <View>
                 <Text style={styles##errorMessageText}>
                   message->React.string
                 </Text>
               </View>
             | Some(Ok(_))
             | None => React.null
             }}
          </View>
        </View>
      </TouchableWithoutFeedback>
      <KeyboardHide>
        <SubmitButton
          valid={form.valid}
          loading={form.submitting}
          submit={form.submit}
        />
      </KeyboardHide>
    </View>
  </View>;
};