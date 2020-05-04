[@react.component]
let app = () =>
  <ReasonRelay.Context.Provider environment=Relay.environment>
    <React.Suspense fallback={<Loading />}>
      <ReactNative.StatusBar barStyle=`lightContent />
      <Router.RootStackScreen />
    </React.Suspense>
  </ReasonRelay.Context.Provider>;