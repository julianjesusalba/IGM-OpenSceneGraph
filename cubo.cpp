#include <osg/Geode>
#include <osg/Geometry>
#include <osg/Material>
#include <osg/ShapeDrawable>
#include <osgViewer/Viewer>
#include <osg/MatrixTransform>

int main() {
    // Creamos un nodo Geode
    osg::ref_ptr<osg::Geode> geode = new osg::Geode();

    // Creamos un cubo utilizando ShapeDrawable
    osg::ref_ptr<osg::ShapeDrawable> cubeDrawable = new osg::ShapeDrawable(new osg::Box(osg::Vec3(), 1.0f));

    // Creamos el estado para los colores
    osg::ref_ptr<osg::StateSet> stateSet = cubeDrawable->getOrCreateStateSet();

    // Añadimos un color a las caras del cubo
    osg::ref_ptr<osg::Vec4Array> colors = new osg::Vec4Array;
    colors->push_back(osg::Vec4(1.0f, 0.0f, 0.0f, 1.0f)); // Rojo
    colors->push_back(osg::Vec4(0.0f, 1.0f, 0.0f, 1.0f)); // Verde
    colors->push_back(osg::Vec4(0.0f, 0.0f, 1.0f, 1.0f)); // Azul
    colors->push_back(osg::Vec4(1.0f, 1.0f, 0.0f, 1.0f)); // Amarillo
    colors->push_back(osg::Vec4(1.0f, 0.0f, 1.0f, 1.0f)); // Magenta
    colors->push_back(osg::Vec4(0.0f, 1.0f, 1.0f, 1.0f)); // Cyan
    cubeDrawable->setColorArray(colors);
    cubeDrawable->setColorBinding(osg::Geometry::BIND_PER_VERTEX);

    osg::ref_ptr<osg::Material> material = new osg::Material;
    material->setColorMode(osg::Material::AMBIENT_AND_DIFFUSE); // Establecer el modo de color
    material->setAmbient(osg::Material::FRONT_AND_BACK, osg::Vec4(0.2f, 0.2f, 0.2f, 1.0f)); // Establecer el color ambiental
    material->setDiffuse(osg::Material::FRONT_AND_BACK, osg::Vec4(0.8f, 0.8f, 0.8f, 1.0f)); // Establecer el color difuso

    // Aplicar el material al conjunto de estado
    stateSet->setAttributeAndModes(material, osg::StateAttribute::ON);

    // Añadimos la forma del cubo al nodo Geode
    geode->addDrawable(cubeDrawable);

    // Creamos un nodo transform para rotar el cubo
    osg::ref_ptr<osg::MatrixTransform> rotateTransform = new osg::MatrixTransform;
    rotateTransform->addChild(geode);

    // Creamos un visor para visualizar la escena
    osg::ref_ptr<osgViewer::Viewer> viewer = new osgViewer::Viewer;

    // Configurar el visor para usar un solo monitor
    viewer->setUpViewInWindow(200, 200, 800, 800); // Tamaño de la ventana
    //viewer->apply(new osgViewer::SingleWindow(200, 200, 800, 800, 0));
    viewer->realize();

    // Cargar tu escena y agregarla al visor
    // osg::ref_ptr<osg::Node> scene = ...; // Tu escena
    viewer->setSceneData(rotateTransform);

    // Ejecutar el visor
    //viewer->run();

    // Configuramos la rotación del cubo
    float angle = 0.0f;
    while (!viewer->done()) {
        osg::Matrix rotationMatrix;
        rotationMatrix.makeRotate(angle, osg::Vec3(0.0f, 1.0f, 0.0f)); // Rotación en el eje Y
        rotateTransform->setMatrix(rotationMatrix);
        angle += 0.01f;
        
        // Alejar la cámara
        osg::Matrixd viewMatrix;
        viewMatrix.makeTranslate(0.0, 0.0, -5.0); // Modifica el último valor para ajustar la distancia
        viewer->getCamera()->setViewMatrix(viewMatrix);

        viewer->frame();
    }

    return 0;
}
