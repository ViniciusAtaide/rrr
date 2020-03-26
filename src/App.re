/**
 * Sample React Native App
 * https://github.com/facebook/react-native
 *
 * Converted from https://github.com/facebook/react-native/blob/724fe11472cb874ce89657b2c3e7842feff04205/template/App.js
 * With a few tweaks
 */

type reactNativeNewAppScreenColors = {
  .
  "primary": string,
  "white": string,
  "lighter": string,
  "light": string,
  "black": string,
  "dark": string,
};

[@bs.module "react-native/Libraries/NewAppScreen"]
external colors: reactNativeNewAppScreenColors = "Colors";

/*
 Here is StyleSheet that is using Style module to define styles for your components
 The main different with JavaScript components you may encounter in React Native
 is the fact that they **must** be defined before being referenced
 (so before actual component definitions)
 More at https://reasonml-community.github.io/reason-react-native/en/docs/apis/Style/
 */
let styles =
  ReactNative.(
    Style.(
      StyleSheet.create({
        "scrollView": style(~backgroundColor=colors##lighter, ()),
        "engine": style(~position=`absolute, ~right=0.->dp, ()),
        "body": style(~backgroundColor=colors##white, ()),
        "sectionContainer":
          style(~marginTop=32.->dp, ~paddingHorizontal=24.->dp, ()),
        "sectionTitle":
          style(~fontSize=24., ~fontWeight=`_600, ~color=colors##black, ()),
        "sectionDescription":
          style(
            ~marginTop=8.->dp,
            ~fontSize=18.,
            ~fontWeight=`_400,
            ~color=colors##dark,
            (),
          ),
        "highlight": style(~fontWeight=`_700, ()),
        "footer":
          style(
            ~color=colors##dark,
            ~fontSize=12.,
            ~fontWeight=`_600,
            ~padding=4.->dp,
            ~paddingRight=12.->dp,
            ~textAlign=`right,
            (),
          ),
      })
    )
  );

module Query = [%relay.query
  {|
  query AppQuery($userId: Int!) {
    userById(id: $userId) {
      name
      email
    }
  }
|}
];

module Internal = {
  open ReactNative;

  [@react.component]
  let make = () => {
    let queryData = Query.use(~variables={userId: 10}, ());

    switch (queryData.userById) {
    | Some(user) =>
      <SafeAreaView>
        <ScrollView
          contentInsetAdjustmentBehavior=`automatic style={styles##scrollView}>
          <View style={styles##body}>
            <View style={styles##sectionContainer}>
              <Text style={styles##sectionDescription}>
                <Text style={styles##highlight}>
                  {(user.name ++ "  ")->React.string}
                </Text>
                <Text> user.email->React.string </Text>
              </Text>
            </View>
          </View>
        </ScrollView>
      </SafeAreaView>
    | None => React.null
    };
  };
};

module Loading = {
  open ReactNative;
  [@react.component]
  let make = () => <View> <Text> "Loadingg"->React.string </Text> </View>;
};

[@react.component]
let make = () =>
  <React.Suspense fallback={<Loading />}> <Internal /> </React.Suspense>;