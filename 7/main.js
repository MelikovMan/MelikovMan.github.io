$(document).ready(function () {
    console.log("ready!");
    $(".imgslide").slick({
        adaptiveHeight: true,
        dots: true,
        infinite: true,
        mobileFirst: true,
        responsive: [
            {
                breakpoint: 600,
                settings: {
                    slidesToScroll: 4,
                    slidesToShow: 4
                }
            },
            {
                breakpoint: 200,
                settings: {
                    slidesToScroll: 2,
                    slidesToShow: 2
                }
            }
        ]
    });
});