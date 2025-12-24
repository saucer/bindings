<hr>

<div align="center"> 
    <img src="https://raw.githubusercontent.com/saucer/saucer.github.io/master/static/img/logo.png" height="312" />
</div>

<p align="center"> 
    C-Bindings for <a href="https://github.com/saucer/saucer">saucer</a>
</p>

---

> [!NOTE]
> The bindings found in this repository do not wrap the C++ API completely.  
> All of the core functionality is wrapped, but serialization heavy parts such as the smartview are not, as it would not make sense to do so.
> Instead, users are encouraged to build their own serialization on top of the bindings provided here, by using the respective event callbacks[^1].

## Existing Bindings

Please checkout the [main repository](https://github.com/saucer/saucer) for the list of available bindings. 
Also, beware that all bindings are community maintained and their conformance may vary.

---

[^1]: For more information, checkout the official repository to see how the smartview is actually implemented under the hood.
