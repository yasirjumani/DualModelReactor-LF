### Dual Model Reactor

```mermaid
graph TD
    Timer --> Phase1Model
    Timer --> Phase2Model

    Phase1Model --> DigitalTwinMonitor
    Phase1Model --> Logger

    Phase2Model --> DigitalTwinMonitor
    Phase2Model --> Logger
```
