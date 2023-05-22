
const handleRangeChange = (labelQuery) => (event) => {
  labelQuery.text(event.target.value);
  console.log(event.target.value);
  console.log(labelQuery);
}

$("#saltinessInput").change(handleRangeChange($("#saltinessValueLabel")));
$("#sournessInput").change(handleRangeChange($("#sournessValueLabel")));
$("#sweetnessInput").change(handleRangeChange($("#sweetnessValueLabel")));
$("#bitternessInput").change(handleRangeChange($("#bitternessValueLabel")));
$("#umamiInput").change(handleRangeChange($("#umamiValueLabel")));
$("#blackInput").change(handleRangeChange($("#blackValueLabel")));
$("#cyanInput").change(handleRangeChange($("#cyanValueLabel")));
$("#magentaInput").change(handleRangeChange($("#magentaValueLabel")));
$("#yellowInput").change(handleRangeChange($("#yellowValueLabel")));


fetch("assets/presets.json")
.then(response => response.json())
.then(data => {
  console.log(data);

  const items = data.items;

  const itemElems = items.map((item, index) => {
    return `<div class="carousel-item ${index === 0 ? "active" : ""}">
      <img src="${item.imgSrc}" class="d-block w-100" alt="${item.itemName}">
    </div>`
  });

  const elemsIndicator = items.map((item, index) => {
    return `<button type="button" data-bs-target="#imageCarousel" data-bs-slide-to="${index}" ${index === 0 ? 'class="active"' : ""} aria-current="true" aria-label="Slide ${index}"></button>`
  });

  $("#imageCarouselItems").append(...itemElems);
  $("#carouselIndicatorItems").append(...elemsIndicator);


  const handleCarouselSlide = (index) => {
    const item = items[index];
    const taste = item.taste;
    console.log(taste);

    $("#saltinessInput").val(taste.salty).attr("disabled", !item.editable);
    $("#sournessInput").val(taste.sour).attr("disabled", !item.editable);
    $("#sweetnessInput").val(taste.sweet).attr("disabled", !item.editable);
    $("#bitternessInput").val(taste.bitter).attr("disabled", !item.editable);
    $("#umamiInput").val(taste.umami).attr("disabled", !item.editable);
    $("#blackInput").val(taste.black).attr("disabled", !item.editable);
    $("#cyanInput").val(taste.cyan).attr("disabled", !item.editable);
    $("#magentaInput").val(taste.magenta).attr("disabled", !item.editable);
    $("#yellowInput").val(taste.yellow).attr("disabled", !item.editable);

    $("#saltinessValueLabel").text(taste.salty);
    $("#sournessValueLabel").text(taste.sour);
    $("#sweetnessValueLabel").text(taste.sweet);
    $("#bitternessValueLabel").text(taste.bitter);
    $("#umamiValueLabel").text(taste.umami);
    $("#blackValueLabel").text(taste.black);
    $("#cyanValueLabel").text(taste.cyan);
    $("#magentaValueLabel").text(taste.magenta);
    $("#yellowValueLabel").text(taste.yellow);
  }

  $("#imageCarousel").on("slid.bs.carousel", (event) => {
    console.log(event);

    handleCarouselSlide(event.to);
  });

  handleCarouselSlide(0);
});

$("#tasteButton").on("click", (event) => {
  const taste = {
    salty: $("#saltinessInput").val(),
    sour: $("#sournessInput").val(),
    sweet: $("#sweetnessInput").val(),
    bitter: $("#bitternessInput").val(),
    umami: $("#umamiInput").val(),
    black: $("#blackInput").val(),
    cyan: $("#cyanInput").val(),
    magenta: $("#magentaInput").val(),
    yellow: $("#yellowInput").val(),
  }
  const url = `/api/sequence?salty=${taste.salty}&sour=${taste.sour}&sweet=${taste.sweet}&bitter=${taste.bitter}&umami=${taste.umami}&black=${taste.black}&cyan=${taste.cyan}&magenta=${taste.magenta}&yellow=${taste.yellow}`;

  console.log(event);
  $(event.currentTarget).attr("disabled", true);
  fetch(url)
    .then(res => {
      console.log(res);
    })
    .catch(err => {
      console.error(err);
    })
    .finally(() => {
      $(event.currentTarget).attr("disabled", false);
    })
})